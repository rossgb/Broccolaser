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

Player::Player(Vector2f velocity, Vector2f position, Rect<int> boundingBox, Sprite sprite) : speed(300)
{
	this->velocity = velocity;
	this->position = position;
	this->boundingBox = boundingBox;
	this->sprite = sprite;
}

void Player::update(float deltaTime)
{
	//handle keyboard input
	handleKeyboard();
	
	Entity::update(deltaTime);
}

void Player::handleKeyboard()
{

	if(RIGHT) {
		sprite.setScale(-1,1);
	} else if (LEFT) {
		sprite.setScale(1,1);
	}
	if(!inair)
	{
		if (LEFT)
		{
			velocity.x = -speed;
		} else if (RIGHT)
		{
			velocity.x = speed;
		} else{
			velocity.x = 0;
		}
	} else {
		if (LEFT && velocity.x >=-300)
		{
			velocity.x -= 5;
		} else if (RIGHT && velocity.x <=300)
		{
			velocity.x += 5;
		}

	}

	if (boundingBox.top+boundingBox.height>=600) {
		inair = false;
	} else {
		inair = true;
	}
	//IF CAN JUMP + UP
	if (UP  && !inair)
	{
		velocity.y = -300;
	//IF ON GROUND
	} else if (!inair) 
	{
		velocity.y = 0;
	//FALLING
	} else {
		velocity.y += 10;
	}
	// if (UP)
	// {
	// 	velocity.y = -speed;
	// } else if (DOWN)
	// {
	// 	velocity.y = speed;
	// } else{
	// 	velocity.y = 0;
	// }
}

Player::~Player()
{
}