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
#define LEFT Keyboard::isKeyPressed(Keyboard::A)
#define RIGHT Keyboard::isKeyPressed(Keyboard::S)
#define UP Keyboard::isKeyPressed(Keyboard::W)
#define DOWN Keyboard::isKeyPressed(Keyboard::R)

using namespace sf;

Player::Player(Vector2f velocity, Vector2f position, Rect<int> boundingBox, Sprite sprite)
{
	this->velocity = velocity;
	this->position = position;
	this->boundingBox = boundingBox;
	this->sprite = sprite;
}

void Player::update()
{
	//handle keyboard input
	handleKeyboard();
	
	Entity::update();
}

void Player::handleKeyboard()
{
	if (LEFT)
	{
		velocity.x = -1;
	} else if (RIGHT)
	{
		velocity.x = 1;
	} else{
		velocity.x = 0;
	}
	
	if (UP)
	{
		velocity.y = -1;
	} else if (DOWN)
	{
		velocity.y = 1;
	} else{
		velocity.y = 0;
	}
}

Player::~Player()
{
}