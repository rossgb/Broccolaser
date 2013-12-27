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

enum stateEnum {
	standing = 0,
	jumping = 2,
	walking = 4,
	attacking = 6,
	charging = 8,
	dashing = 10
};

class Player : public Entity
{
	
	
public:
	Player(Vector2f position, Texture* texture);
	~Player();

	void update(float deltaTime, std::vector<Entity*> touching, std::vector<Event> events);

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


