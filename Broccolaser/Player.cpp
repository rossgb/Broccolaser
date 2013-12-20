//
//  Player.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-19.
//
//

#include "Player.h"

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
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		//go left
		velocity.x = -1;
	} else if (Keyboard::isKeyPressed(Keyboard::S))
	{
		//go right
		velocity.x = 1;
	} else{
		velocity.x = 0;
	}
	
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		//go up
		velocity.y = -1;
	} else if (Keyboard::isKeyPressed(Keyboard::R))
	{
		velocity.y = 1;
	} else{
		velocity.y = 0;
	}
}

Player::~Player()
{
}