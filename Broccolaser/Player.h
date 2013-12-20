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

class Player : public Entity{
	
	
public:
	Player(Vector2f velocity, Vector2i position, Rect<int> boundingBox, Sprite sprite);

};

#endif /* defined(__Broccolaser__Player__) */
