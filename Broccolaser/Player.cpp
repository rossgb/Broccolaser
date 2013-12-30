//
//  Player.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-19.
//
// this is what the user controls, the player inherits from entity, and adds functionality to
// handle keyboard input

#include "Player.h"


//later if we want to change the controls programatically, we should turn this into an enum
#define LEFT Keyboard::isKeyPressed(Keyboard::Left)
#define RIGHT Keyboard::isKeyPressed(Keyboard::Right)
#define UP Keyboard::isKeyPressed(Keyboard::Up)
#define DOWN Keyboard::isKeyPressed(Keyboard::Down)
#define SPACE Keyboard::isKeyPressed(Keyboard::Space)


using namespace sf;

Player::Player(Vector2f position, Texture* texture) :
	speed(250), jumpPower(550), dashPow(700), jumpVel(0), inair(true), stateTimer(0),
	ground(NULL), facingLeft(false), maxStateTime(0.3), health(10)
{
	this->velocity = Vector2f(0,0);
	this->position = position;
	this->sprite = Sprite(*texture, IntRect(0,0,48,88));
	this->boundingBox = IntRect(0,0,48,88);
	this->type = PLAYER;
	invulTimer = Clock();
	this->state = jumping;
}

void Player::update(float deltaTime, std::vector<Entity*> touching, std::vector<Event> events)
{
	Entity::update(deltaTime, touching, events);

	//handle keyboard input
	handleKeyboard(events, deltaTime);
	//handle collisions
	handleCollisions(touching);	

	
	if (ground != NULL)
	{
		//moving platforms
		position += ground->velocity * deltaTime;
	}

	stateTimer += deltaTime;
	if (stateTimer >= maxStateTime)
	{
		stateChange++;
		stateTimer = 0;
	}

	handleState();
	
	// /!\ HACK ZONE
	if (position.y > 2000)
	{
		position = Vector2f(0,0);
		velocity = Vector2f(0,0);
	}
}

void Player::handleState()
{
	int prevState = state;
	
	maxStateTime = (state < attacking) ? 0.3 : 0.08;

	if (stateChange >= 4) // 4 is the amount of frames wide the player is
	{
		//do this stuff at end of animations
		stateChange = 0;
		if (state == attacking)
		{
			state = (SPACE) ? charging : standing;
		} else if (state == dashing)
		{
			state = jumping;
		} 
	}
	
	if (state < attacking)
	{
		//no attacking going on, regular logic for animations
		if (velocity.y != 0)
		{
			state = jumping;
		} else if (velocity.x != 0)
		{
			state = walking;
		} else
		{
			state = standing;
		}
	}
	

	// if (state == charging && !SPACE)
	// {
	// 	//no dash
	// 	state = standing;
	// }
	

	if (prevState != state) {
		stateChange = 0;
	}
	//std::cout << (75*stateChange) << " " << 75*(0+(int)facingLeft) << "\n";
	sprite.setTextureRect(IntRect(50*stateChange,90*(state+(int)facingLeft),48,87));
	
}

void Player::handleCollisions(std::vector<Entity*> touching)
{
	ground = NULL;
	IntRect feet(boundingBox);
	feet.height = 10;
	feet.top += boundingBox.height - 10;
	feet.left += 5;
	feet.width -= 10;
	
	IntRect head(boundingBox);
	head.height = 10;
	head.left += 5;
	head.width -= 10;

	IntRect left(boundingBox);
	left.width = 10;
	left.height -= 20;
	left.top += 10;
	
	IntRect right(boundingBox);
	right.width = 10;
	right.left += boundingBox.width - 10;
	right.height -= 20;
	right.top += 10;
	
	for (Entity* entity : touching)
	{
		switch (entity->type) {
			case ENVIRONMENTOBJECT:
				if (feet.intersects(entity->boundingBox))
				{
					if (ground != NULL && ground->position.y < entity->position.y) continue;
					ground = entity;
				} else if(head.intersects(entity->boundingBox))
				{
					//kill upward velocity
					if (velocity.y < 0)
					{
						velocity.y = 0;
					}
				}
				if (right.intersects(entity->boundingBox))
				{
					//kill horizontal velocity
					if (velocity.x > 0 && entity != ground)
					{
						velocity.x = 0;
					}
				}
				if (left.intersects(entity->boundingBox))
				{
					//kill horizontal velocity
					if (velocity.x < 0 && entity != ground)
					{
						velocity.x = 0;
					}
				}
				
				break;
			case ENEMY:
				if (invulTimer.getElapsedTime().asSeconds() > 0.5) //make this a variable
				{
					health--;
					velocity.x += (position.x > entity->position.x) ? 300 : -300;
					velocity.y -= 300;
					invulTimer.restart();
				}
				break;
		}

	}
	if (ground != NULL)
	{
		//lock player to the ground
		if(velocity.y >= 0)
		{
			position.y = ground->boundingBox.top - boundingBox.height + 1;
		}
	}
	
}

void Player::handleKeyboard(std::vector<Event> events, float deltaTime)
{
	// physics constants
	int terminalVelocity = 1500;
	float accel = 2500 * deltaTime;
	float gravity = 3000 * deltaTime;
	float friction = 2000 * deltaTime;
	float jumpFriction = 1000 * deltaTime;
 
	for (Event event : events)
	{
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space && state < attacking)
		{
			state = attacking;
			stateChange = 0;
		}
		if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space)
		{
			if (state == charging)
			{
				state = dashing;
				velocity.x = (facingLeft) ? -dashPow : dashPow;
			} else if (state != attacking)
			{
				stateChange = 0;
			}
		}
	}
	
	//make the player face the direction he's moving
	if(RIGHT) {
		facingLeft = false;
	} else if (LEFT) {
		facingLeft = true;
	}
	
 	inair = (ground == NULL) ? true : false;
 	
	//airborne specifics
	accel = (inair) ? accel/5 : accel;
	friction = (inair) ? friction/5 : friction;
	
	//control left and right
	if (LEFT && velocity.x > -speed)
	{
		velocity.x -= accel;
	} else if (RIGHT && velocity.x < speed)
	{
		velocity.x += accel;
	} else if (velocity.x > friction || velocity.x < -friction)
	{
		//no keys pressed? slow down!
		velocity.x -= (velocity.x > 0) ? friction : -friction;
	} else
	{
		velocity.x = 0;
	}
	
	//vertical stuff:
	
	if (inair)
	{
		//fall by gravity
		velocity.y = (velocity.y > terminalVelocity) ? terminalVelocity : velocity.y + gravity;
		
		//reduce jumpvel
		jumpVel = (jumpVel < 0) ? 0 : jumpVel - jumpFriction;
	} else
	{
		//if we're going down, then stop and reset jump
		if (velocity.y >= 0)
		{
			velocity.y = (velocity.y > 900) ? -200 : 0; // bounce
			jumpVel = jumpPower;
		} else
		{
			//if we're going up, ignore the ground

			//fall by gravity
			velocity.y = (velocity.y > terminalVelocity) ? terminalVelocity : velocity.y + gravity;
			
			//reduce jumpvel
			jumpVel = (jumpVel < 0) ? 0 : jumpVel - jumpFriction;
		}
	}
	
	//IF CAN JUMP + UP
	if (UP)
	{
		if (!inair)
		{
			velocity.y = -jumpPower;
			jumpVel = 1500;
		}
		velocity.y -= jumpVel * deltaTime;
	} else
	{
		jumpVel = 0;
	}
}

Player::~Player()
{
}