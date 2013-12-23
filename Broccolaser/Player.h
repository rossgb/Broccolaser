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
	Player(Vector2f velocity, Vector2f position, Rect<int> boundingBox, Sprite sprite);
	~Player();

	void update(float deltaTime, std::vector<Entity*> touching);

private:
	int speed;
	bool inair;
	
	void handleKeyboard();
	
};

#endif /* defined(__Broccolaser__Player__) */