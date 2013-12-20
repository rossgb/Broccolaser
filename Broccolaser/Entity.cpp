//
//  Entity.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-19.
//
//

#include "Entity.h"

using namespace sf;

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}

void Entity::update()
{
	position = position + velocity;
	sprite.setPosition(position);
	boundingBox = IntRect((Vector2i)position, Vector2i(20,60));
}