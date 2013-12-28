#include "PlayerAttack.h"

#define SPACE Keyboard::isKeyPressed(Keyboard::Space)
#define SPACEUP Keyboard::isKeyReleased(Keyboard::Space)

using namespace sf;

PlayerAttack::PlayerAttack(Player* player, Texture* texture)
{
	this->player = player;
	this->velocity = Vector2f(0,0);
	this->position = player->position;
	this->sprite = Sprite(*texture,IntRect(50,0,74,74));
	this->boundingBox = IntRect((player->position.x)+40,(player->position.y)+60,50,70);
	this->type = PLAYERATTACK;
}

void PlayerAttack::update(float deltaTime, std::vector<Entity*> touching, std::vector<Event> events)
{
	Entity::update(deltaTime, touching, events);

	if(player->facingLeft) {
		position.x = player->position.x-65;
	} else {	
		position.x = player->position.x+30;
	}
	position.y = player->position.y;
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
	if (player->state >=0 && player->state <=4 || player->state == 8)
	{
		sprite.setTextureRect(IntRect((75*player->stateChange),75*(4+(int)player->facingLeft),75,75));
		//std::cout << (75*player->stateChange) << " " << 75*(4+(int)player->facingLeft) << "\n";
    } else if (player->state == 6) {
    	sprite.setTextureRect(IntRect((75*player->stateChange),75*(0+(int)player->facingLeft),75,75));
    } else {
    	sprite.setTextureRect(IntRect((75*player->stateChange),75*(2+(int)player->facingLeft),75,75));
    }
}

void PlayerAttack::attack(int pos)
{
	if(SPACE) {}
}

PlayerAttack::~PlayerAttack()
{
}