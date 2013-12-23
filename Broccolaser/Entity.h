//
//  Entity.h
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-19.
//
//

#ifndef __Broccolaser__Entity__
#define __Broccolaser__Entity__

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class Entity : public sf::Drawable
{
	
public:
	virtual void update(float deltaTime, std::vector<Entity*> touching);
	
	Vector2f velocity;
	Vector2f position;
	Rect<int> boundingBox;
	Sprite sprite;
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif /* defined(__Broccolaser__Entity__) */
