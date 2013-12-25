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


using namespace sf;

Player::Player(Vector2f position, Texture* texture) :
	speed(250), jumpPower(150), jumpVel(0), ground(NULL), facingLeft(true)
{
	this->velocity = Vector2f(0,0);
	this->position = position;
	this->sprite = Sprite(*texture, IntRect(Vector2i(0,0), (Vector2i)texture->getSize()));
	this->boundingBox = IntRect(Vector2i(0,0),(Vector2i)sprite.getTexture()->getSize());
	//this->sprite.setOrigin(boundingBox.width/2,0);
}

void Player::update(float deltaTime, std::vector<Entity*> touching)
{
	//handle collisions
	handleCollisions(touching);
	//handle keyboard input
	handleKeyboard();
	
	// /!\ HACK ZONE
	if (position.y > 800)
	{
		position = Vector2f(90,90);
	}
			
	Entity::update(deltaTime, touching);
}

void Player::handleCollisions(std::vector<Entity*> touching)
{
	ground = NULL;
	inair = true;
	Rect<int> feet(boundingBox);
	feet.top += boundingBox.height / 4.0f;
	feet.height -= boundingBox.height / 4.0f;
	feet.left += 5;
	feet.width -= 10;
	
	for (Entity* entity : touching)
	{
		//TODO: ensure entity is something we can land on e.g., an EnvironmentObject
		if (feet.intersects(entity->boundingBox))
		{
			inair = false;
			ground = entity;
		}
	}
	if (ground != NULL && !UP)
	{
		//lock player to the ground
		position.y = ground->boundingBox.top - boundingBox.height + 1;
	}
}

void Player::handleKeyboard()
{
	//physics constants
	int terminalVelocity = 2300;
	int accel = 25;
	int gravity = 30;
	int friction = 20;
	
	//make the player face the direction he's moving
	//sprite.setOrigin(boundingBox.left+boundingBox.width/2,boundingBox.top+boundingBox.height/2);
	if(RIGHT) {
		//sprite.setScale(-1,1);
		
	} else if (LEFT) {
		sprite.setScale(1,1);
	}
	
	
	//check collisions
	
	//airborne specifics
	accel = (inair) ? accel/5 : accel;
	friction = (inair) ? friction/5 : friction;
	
	//control left and right
	if (LEFT)
	{
		velocity.x -= accel;
	} else if (RIGHT)
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
	
	//IF CAN JUMP + UP
	if (UP)
	{
		velocity.y -= jumpVel;
		if (velocity.y < 0)
		{
			inair = true; // if we're going up, then we're in the air
		}
	} else
	{
		//no jumpy if we've already jumped. If we're on the ground, this will get set to the jump power in the next step
		jumpVel = 0;
	}
	
	if (!inair)
	{
		//if we're on the ground, reset our jump
		jumpVel = jumpPower;
		velocity.y = 0;
	} else {
		//FALLING
		jumpVel /=1.1;
		
		if (velocity.y < terminalVelocity)
		{
			velocity.y += gravity;
		}
	}
	
	//limit the player's max speed
	if(velocity.x > speed)
	{ 
		velocity.x = speed;
	} else if (velocity.x < -speed)
	{
		velocity.x = -speed;
	}
}

Player::~Player()
{
}