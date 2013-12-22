//
//  Background.h
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-22.
//
//

#ifndef __Broccolaser__Background__
#define __Broccolaser__Background__

#include <iostream>
#include <SFML/graphics.hpp>

using namespace sf;

class Background : public sf::Drawable
{
	
public:
	Background(Texture* t1, Texture* t2, Texture* t3);
	
	Sprite background;
	Sprite midground;
	Sprite foreground;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* defined(__Broccolaser__Background__) */
