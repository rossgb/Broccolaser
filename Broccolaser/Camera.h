//
//  Camera.h
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-19.
//
//

#ifndef __Broccolaser__Camera__
#define __Broccolaser__Camera__

#include <iostream>
#include "Entity.h"
#include "Player.h"

using namespace sf;

class Camera
{
	
	
public:
	Camera(Player* player,View* view);
	~Camera();

	void update();

private:
	Vector2f position;
	Player* player;
	View* view;

	
};

#endif /* defined(__Broccolaser__Camera__) */
