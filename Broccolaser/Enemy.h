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

	void update(float deltaTime, std::vector<Entity*> touching);

private:
	void think();
	void applyPhysics();
	void handleCollisions(std::vector<Entity *> touching);
	
	float jumpVel;
	float jumpPower;
	bool inair;
	bool facingLeft;
	Entity* ground;
};

#endif /* defined(__Broccolaser__Enemy__) */
