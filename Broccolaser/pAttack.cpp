#include "pAttack.h"

#define SPACE Keyboard::isKeyPressed(Keyboard::Space)
#define SPACEUP Keyboard::isKeyReleased(Keyboard::Space)

using namespace sf;

pAttack::pAttack(Player* player, Texture* texture)
{
	this->player = player;
	this->velocity = Vector2f(0,0);
	this->position = player->position;
	this->sprite = Sprite(*texture,IntRect(0,0,50,70));
	this->boundingBox = IntRect(player->position.x+40,player->position+60,50,70);
}

void pAttack::update(float deltaTime, std:vector<Endtity*> touching)
{
	Entity::update(deltaTime, touching);


	tateTimer += deltaTime;
	if (stateTimer >= .1)
	{
		stateChange++;
		stateTimer = 0;
	}

	if (stateChange >= 4)
	{
		stateChange = 0;
	}
	
	attack(stateChange);


}

void pAttack:attack(int pos)
{
	if(SPACE) 

	}
}