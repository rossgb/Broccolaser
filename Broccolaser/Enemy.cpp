//
//  Enemy.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-24.
//
//

#include "Enemy.h"

Enemy::Enemy(Vector2f position, Texture* texture)
{
	this->velocity = Vector2f(0,0);
	this->position = position;
	this->sprite = Sprite(*texture, IntRect(Vector2i(0,0), (Vector2i)texture->getSize()));
	this->boundingBox = IntRect(Vector2i(0,0),(Vector2i)sprite.getTexture()->getSize());
}