//
//  Player.h
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-19.
//
//

#ifndef __Broccolaser__Player__
#define __Broccolaser__Player__

#include <iostream>
#include "Entity.h"

using namespace sf;

class Player : public Entity
{
	
	
public:
	Player(Vector2f position, Texture* texture);
	~Player();

	void update(float deltaTime, std::vector<Entity*> touching);

private:
	int state;
	float stateTimer;
	int stateChange;


	int speed;
	int jumpPower;
	int jumpVel;
	int dashPow;

	bool attack1;
	bool attack2;
	float maxStateTime;

	bool inair;
	bool facingLeft;
	Entity* ground;
	
	void handleKeyboard();
	void handleCollisions(std::vector<Entity*> touching);
	void handleState(int pos);	
};

#endif /* defined(__Broccolaser__Player__) */


