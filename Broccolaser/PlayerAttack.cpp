#include "PlayerAttack.h"

#define SPACE Keyboard::isKeyPressed(Keyboard::Space)
#define SPACEUP Keyboard::isKeyReleased(Keyboard::Space)

using namespace sf;

PlayerAttack::PlayerAttack(Player* player, Texture* texture)
{
	this->player = player;
	this->velocity = Vector2f(0,0);
	this->position = player->position;
	this->sprite = Sprite(*texture,IntRect(0,0,50,70));
	this->boundingBox = IntRect((player->position.x)+40,(player->position.y)+60,50,70);
}

void PlayerAttack::update(float deltaTime, std::vector<Entity*> touching, std::vector<Event> events)
{
	Entity::update(deltaTime, touching, events);


	// stateTimer += deltaTime;
	// if (stateTimer >= .1)
	// {
	// 	stateChange++;
	// 	stateTimer = 0;
	// }

	// if (stateChange >= 4)
	// {
	// 	stateChange = 0;
	// }
	
	// attack(stateChange);


}

void PlayerAttack::attack(int pos)
{
	if(SPACE) {}
}