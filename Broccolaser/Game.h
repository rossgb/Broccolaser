//
//  Game.h
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-18.
//
//

#ifndef __Broccolaser__Game__
#define __Broccolaser__Game__

#include <iostream>
#include "Entity.h"
#include "Player.h"

using namespace sf;

class Game
{
	
public:
	RenderWindow* window;
	std::vector<Entity*> entityList;
	
	Game(RenderWindow* window);
	void setup();
	void run ();
 	void createPlayer();
	
private:
	Player* p1;
	void cleanup();
	
};

#endif /* defined(__Broccolaser__Game__) */
