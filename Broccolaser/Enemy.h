//
//  Enemy.h
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-24.
//
//

#ifndef __Broccolaser__Enemy__
#define __Broccolaser__Enemy__

#include <iostream>
#include "Entity.h"

using namespace sf;

class Enemy : public Entity
{
public:
	Enemy(Vector2f position, Texture* texture);
	
};

#endif /* defined(__Broccolaser__Enemy__) */
