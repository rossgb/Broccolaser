//
//  EnvironmentObject.h
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-22.
//
//

#ifndef __Broccolaser__EnvironmentObject__
#define __Broccolaser__EnvironmentObject__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity.h"

using namespace sf;

class EnvironmentObject : public Entity
{
	
public:
	EnvironmentObject(Vector2f velocity, Vector2f position, Rect<int> boundingBox, Sprite sprite);
	EnvironmentObject();
		
private:
	void update(float deltaTime);
};

#endif /* defined(__Broccolaser__EnvironmentObject__) */
