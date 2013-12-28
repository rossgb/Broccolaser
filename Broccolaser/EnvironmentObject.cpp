//
//  EnvironmentObject.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-22.
//
//

#include "EnvironmentObject.h"

EnvironmentObject::EnvironmentObject(Vector2f position, Texture* texture, Vector2i repeat)
{
	texture->setRepeated(true);
	repeat.x *= texture->getSize().x;
	repeat.y *= texture->getSize().y;
	this->velocity = Vector2f(0,0);
	this->position = position;
	this->boundingBox = IntRect((Vector2i)position,repeat);
	this->sprite = Sprite(*texture, IntRect(Vector2i(0,0), repeat));
	this->type = ENVIRONMENTOBJECT;
}

void EnvironmentObject::update(float deltaTime, std::vector<Entity*> touching, std::vector<Event> events)
{
	//std::cout << this->position.x;
	//std::cout << this->boundingBox.top << std::endl;
	//std::cout << this->sprite.getTextureRect().top;

	
	Entity::update(deltaTime, touching, events);
}

EnvironmentObject::~EnvironmentObject()
{
}