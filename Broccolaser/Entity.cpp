//
//  Entity.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-19.
//
// This is the base class which Players, enemies, projectiles, environment etc. will inherit from
// in the Game class, there is a list of entities that will be drawn

#include "Entity.h"

using namespace sf;

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void Entity::update(float deltaTime, std::vector<Entity*> touching, std::vector<Event> events)
{	
	position += velocity * deltaTime;
	sprite.setPosition(position);
	boundingBox.top = position.y;
	boundingBox.left = position.x;
}