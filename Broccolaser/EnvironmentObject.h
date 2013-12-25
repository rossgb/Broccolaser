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
	EnvironmentObject(Vector2f position, Texture* texture, Vector2i repeat);
	EnvironmentObject();
		
private:
	void update(float deltaTime, std::vector<Entity*> touching);
};

#endif /* defined(__Broccolaser__EnvironmentObject__) */
