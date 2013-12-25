//
//  EnvironmentObject.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-22.
//
//

#include "EnvironmentObject.h"

EnvironmentObject::EnvironmentObject(Vector2f velocity, Vector2f position, Rect<int> boundingBox, Sprite sprite)
{
	this->velocity = velocity;
	this->position = position;
	this->boundingBox = boundingBox;
	this->sprite = sprite;
}

void EnvironmentObject::update(float deltaTime, std::vector<Entity*> touching)
{
	//std::cout << this->position.x;
	//std::cout << this->boundingBox.top << std::endl;
	//std::cout << this->sprite.getTextureRect().top;

	
	Entity::update(deltaTime, touching);
}