//
//  Player.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-19.
//
//

#include "Player.h"

Player::Player(Vector2f velocity, Vector2i position, Rect<int> boundingBox, Sprite sprite)
{
	this->velocity = velocity;
	this->position = position;
	this->boundingBox = boundingBox;
	this->sprite = sprite;
}
