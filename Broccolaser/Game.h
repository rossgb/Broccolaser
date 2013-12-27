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
#include "Background.h"
#include "Camera.h"
#include "Enemy.h"


using namespace sf;

class Game
{
	
public:
	RenderWindow* window;
	
	Game(RenderWindow* window);
	~Game();
	void setup();
	void run();
	
private:
	std::vector<Entity*> entityList;
	Background* background;
	Text fps;
	View view;
	Camera* camera;
	
	std::string resolvePath(std::string);
	void createPlayer();
	void createBackground();
	void createEnemy(int, int);
	std::vector<Entity*> collide(Entity*);
	void createEnvironment(int, int, int, int);
	void cleanup();

};

#endif /* defined(__Broccolaser__Game__) */
