
#ifndef __Broccolaser__pAttack__
#define __Broccolaser__pAttack__

#include <iostream>
#include "Entity.h"
#include "Player.h"

using namespace sf;

class pAttack : public Entity
{
	
	
public:
	pAttack(Player* player, Texture* texture);
	~pAttack();

	void update(float deltaTime, std::vector<Entity*> touching);

private:
	bool active;
	int attackNumber;
	float stateTimer;
	int stateChange;
	Player* player;
	
	void handleKeyboard();
	void handleState(int pos);

	
};

#endif /* defined(__Broccolaser__pAttack__) */


