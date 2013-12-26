#include "Camera.h"

using namespace sf;

Camera::Camera(Player* player, View* view)
{
	this->player = player;
	this->view = view;
	this->position = player->position;
}

void Camera::update()
{
	Vector2f target(player->position.x + player->boundingBox.width/2, player->position.y + player->boundingBox.height/2);
	Vector2f velocity(target.x - position.x, target.y - position.y);
	velocity /= 5.0f;
	
	//view->setRotation(position.y); //OH GOD
	
	position += velocity;
	
	view->setCenter(position);
}