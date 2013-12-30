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

position.y = player->position.y+30;
	if(player->facingLeft) {
		position.x = player->position.x-65;
		if (player->state == attacking) {
			if(player->stateChange <= 1) {
				position.x = player->position.x-10;
				position.y = player->position.y-20;
			} else if (player->stateChange == 2) {
				position.x = player->position.x-55;
				position.y = player->position.y-20;
			} else if (player->stateChange == 3) {
				position.x = player->position.x+-50;
				position.y = player->position.y+5;
			}
	}

	} else {	
		position.x = player->position.x+30;
		if (player->state == attacking) {
			if(player->stateChange <= 1) {
				position.x = player->position.x-10;
				position.y = player->position.y-20;
			} else if (player->stateChange == 2) {
				position.x = player->position.x+20;
				position.y = player->position.y-20;
			} else if (player->stateChange == 3) {
				position.x = player->position.x+25;
				position.y = player->position.y+5;
			}
	}
	}
	
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
	
	if (player->state <= walking || player->state == charging)
	{
		sprite.setTextureRect(IntRect((75*player->stateChange),75*(4+(int)player->facingLeft),75,75));
		active = false;
    } else if (player->state == attacking) {
    	sprite.setTextureRect(IntRect((75*player->stateChange),75*(0+(int)player->facingLeft),75,75));
		active = true;
    } else {
		active = true;
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