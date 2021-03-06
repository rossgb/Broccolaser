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

//requirement, attacking stuff goes on after 6(attacking)
//if you want to change that, change the code in Player.cpp handleState()
enum playerStateEnum {
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
	int stateChange;
	bool facingLeft;
private:
	
	float stateTimer;
	float maxStateTime;
	
	float maxheight;
	int speed;
	int jumpPower;
	int jumpVel;
	int dashPow;
	int health;

	bool inair;
	
	Clock invulTimer;
	
	Entity* ground;
	
	void handleKeyboard(std::vector<Event> events, float deltaTime);
	void handleCollisions(std::vector<Entity*> touching);
	void handleState();	
};

#endif /* defined(__Broccolaser__Player__) */


