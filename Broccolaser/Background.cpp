//
//  Background.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-22.
//
//

#include "Background.h"

Background::Background(Texture* t1, Texture* t2, Texture* t3)
{
	background.setTexture(*t1);
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background);
	//target.draw(midground);
	//target.draw(foreground);
}