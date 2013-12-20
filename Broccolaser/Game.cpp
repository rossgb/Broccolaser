//
//  Game.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-18.
//
// The game class will be the go-between from game knowledge to screen knowledge
// it will include sfml stuff as well as game objects.
// draw loop happens here
// contains a list of Entities

#include <SFML/Graphics.hpp>
#include <assert.h>

#include "ResourcePath.hpp"
#include "Game.h"

Game::Game(RenderWindow* w)
{
	window = w;
}

void Game::setup()
{
	//lets create a player
	createPlayer();
}

void Game::createPlayer()
{
	Vector2f velocity(0,0);
	Vector2f position(20,20);
	Texture texture;
	texture.loadFromFile(resourcePath() + "cute_image.jpg");
	Rect<int> boundingBox((Vector2i)position, Vector2i(20,60));
	Sprite sprite(texture, boundingBox);
	Player* player = new Player(velocity, position, boundingBox, sprite);
	entityList.push_back(player);
	p1 = player;
}
void Game::cleanup()
{
	//maybe this should be in a destructor for Game and called by main.cpp after running the game?
	for (Entity* entity : entityList)
	{
		delete entity;
	}
}

void Game::run ()
{	
	// Start the game loop
    while (window->isOpen())
    {
        // Process events
        Event event;
        while (window->pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::Closed)
			{
                window->close();
            }
			
            // Espace pressed : exit
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
                //open menu
            }
        }
        // Clear screen
        window->clear();
		
		for (Entity* entity : entityList)
		{
			entity->update();
			window->draw(*entity);

		}
		
        // Update the window
        window->display();
    }
	
	cleanup();
}
