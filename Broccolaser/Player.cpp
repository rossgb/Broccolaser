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
	speed(250), jumpPower(150), dashPow(700), jumpVel(0),
	ground(NULL), facingLeft(false), state(jumping), maxStateTime(0.3)
{
	this->velocity = Vector2f(0,0);
	this->position = position;
	this->sprite = Sprite(*texture, IntRect(0,0,48,88));
	this->boundingBox = IntRect(0,0,48,88);
}

void Player::update(float deltaTime, std::vector<Entity*> touching, std::vector<Event> events)
{
	Entity::update(deltaTime, touching, events);

	//handle collisions
	handleCollisions(touching);	
	//handle keyboard input
	handleKeyboard(events);
	
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
	if (position.y > 800)
	{
		position = Vector2f(0,0);
	}
}

void Player::handleState()
{
	int prevState = state;
	
	maxStateTime = (state < attacking) ? 0.3 : 0.05;

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
	Rect<int> feet(boundingBox);
	feet.height = 10;
	feet.top += boundingBox.height - 10;
	feet.left += 5;
	feet.width -= 10;
	
	for (Entity* entity : touching)
	{
		//TODO: ensure entity is something we can land on e.g., an EnvironmentObject
		if (feet.intersects(entity->boundingBox))
		{
			ground = entity;
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

void Player::handleKeyboard(std::vector<Event> events)
{
	// physics constants
	int terminalVelocity = 1500;
	int accel = 25;
	int gravity = 30;
	int friction = 20;
 
	for (Event event : events)
	{
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space && state < attacking)
		{
			state = attacking;
			stateChange = 0;
		}
		if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space)
		{
			if (state != attacking)
			{
				state = dashing;
				velocity.x += (facingLeft) ? -dashPow : dashPow;
			}

			stateChange = 0;
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

	//IF CAN JUMP + UP
	if (UP)
	{
		if (!inair)
		{
			position.y -= 1;
		}
		velocity.y -= jumpVel;
	} else
	{
		jumpVel = 0;
	}
	
	if (inair)
	{
		//fall by gravity
		velocity.y = (velocity.y > terminalVelocity) ? terminalVelocity : velocity.y + gravity;
		
		//reduce jumpvel
		jumpVel = (jumpVel < 0) ? 0 : jumpVel - 10;
	} else
	{
		//if we're going down, then stop and reset jump
		//if we're going up, ignore the ground
		if (velocity.y >= 0)
		{
			velocity.y = (velocity.y > 900) ? -200 : 0; // bounce
			jumpVel = jumpPower;
		} else
		{
			//fall by gravity
			velocity.y = (velocity.y > terminalVelocity) ? terminalVelocity : velocity.y + gravity;
			
			//reduce jumpvel
			jumpVel = (jumpVel < 0) ? 0 : jumpVel - 10;
		}
	}
}

Player::~Player()
{
}