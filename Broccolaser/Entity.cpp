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
