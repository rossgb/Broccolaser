
#ifndef __Broccolaser__PlayerAttack__
#define __Broccolaser__PlayerAttack__

#include <iostream>
#include "Entity.h"
#include "Player.h"

using namespace sf;

class PlayerAttack : public Entity
{
	
	
public:
	PlayerAttack(Player* player, Texture* texture);
	~PlayerAttack();

	void update(float deltaTime, std::vector<Entity*> touching, std::vector<Event> events);

private:
	bool active;
	int attackNumber;
	float stateTimer;
	int stateChange;
	Player* player;
	
	void handleKeyboard();
	void attack(int pos);

	
};

#endif /* defined(__Broccolaser__PlayerAttack__) */


