#include "Camera.h"

using namespace sf;

Camera::Camera(Player* player, View* view)
{
	this->player = player;
	this->view = view;
}

void Camera::update()
{
	view->setCenter(player->position.x + player->boundingBox.width/2, player->position.y + player->boundingBox.height/2);
}