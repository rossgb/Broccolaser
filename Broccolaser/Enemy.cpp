//
//  Enemy.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-24.
//
//

#include "Enemy.h"
#include "math.h"

Enemy::Enemy(Vector2f position, Texture* texture) :
	jumpPower(50), jumpVel(0), ground(NULL), facingLeft(true)
{
	this->velocity = Vector2f(0,0);
	this->position = position;
	this->sprite = Sprite(*texture, IntRect(Vector2i(0,0), (Vector2i)texture->getSize()));
	this->boundingBox = IntRect(Vector2i(0,0),(Vector2i)sprite.getTexture()->getSize());
}

void Enemy::update(float deltaTime, std::vector<Entity *> touching)
{
	Entity::update(deltaTime, touching);
	
	handleCollisions(touching);
	
	think();
	
	applyPhysics();
}

void Enemy::handleCollisions(std::vector<Entity *> touching)
{
	ground = NULL;
	Rect<int> feet(boundingBox);
	feet.height = 10;
	feet.top += boundingBox.height - 10;
	feet.left += 5;
	feet.width -= 10;
	
	for (Entity* entity : touching)
	{
		//TODO: ensure entity is something we can land on e.g., an EnvironmentObject
		if (feet.intersects(entity->boundingBox))
		{
			ground = entity;
		}
	}
	if (ground != NULL)
	{
		//lock player to the ground
		if(velocity.y >= 0)
		{
			position.y = ground->boundingBox.top - boundingBox.height + 1;
		}
	}
}

void Enemy::think()
{
	//is the player nearby?
	//are we about to walk off an edge?
	float middle = position.x + boundingBox.width/2;
	if (ground != NULL)
	{
		if (facingLeft && std::abs((int)(middle - ground->position.x)) < 10)
		{
			//too close to left edge
			facingLeft = false;
		} else if (!facingLeft && std::abs((int)(middle - (ground->position.x+ground->boundingBox.width))) < 10)
		{
			//too close to right edge
			facingLeft = true;
		}
	}
	if (facingLeft)
	{
		velocity.x = -100;
	} else
	{
		velocity.x = 100;
	}
}

void Enemy::applyPhysics()
{
	//physics constants
	int terminalVelocity = 1500;
	int gravity = 30;

	inair = (ground == NULL) ? true : false;
	
	if (inair)
	{
		//fall by gravity
		velocity.y = (velocity.y > terminalVelocity) ? terminalVelocity : velocity.y + gravity;
		
		//reduce jumpvel
		jumpVel = (jumpVel < 0) ? 0 : jumpVel - 10;
	} else
	{
		//if we're going down, then stop and reset jump
		//if we're going up, ignore the ground
		if (velocity.y >= 0)
		{
			velocity.y = (velocity.y > 900) ? -200 : 0; // bounce
			jumpVel = jumpPower;
		} else
		{
			//fall by gravity
			velocity.y = (velocity.y > terminalVelocity) ? terminalVelocity : velocity.y + gravity;
			
			//reduce jumpvel
			jumpVel = (jumpVel < 0) ? 0 : jumpVel - 10;
		}
	}
}