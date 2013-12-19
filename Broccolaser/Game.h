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

using namespace sf;

class Game {
	RenderWindow* window;
	
public:
	Game(RenderWindow* window);
	void run ();
};

#endif /* defined(__Broccolaser__Game__) */
