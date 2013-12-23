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

#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif

#include "Game.h"
#include "EnvironmentObject.h"

#define DEVELOPER true

Game::Game(RenderWindow* w)
{
	window = w;
}

void Game::setup()
{
	//lets create a player
	createPlayer();
	
	createBackground();
	
	createEnvironment(0, 572, 10, 1);

	createEnvironment(650, 572, 10, 1);
	
	if (DEVELOPER)
	{
		Font* font = new Font();
		font->loadFromFile(resolvePath("sansation.ttf"));
		fps = Text("FPS: 0", *font, 16);
		fps.setPosition(window->getSize().x-100, 0);
		fps.setColor(Color::Black);
	}
	//cool idea: if we can save a level as a a file, we can read from that and programatically create the level
}

std::string Game::resolvePath(std::string str)
{
#ifdef __APPLE__
	return resourcePath() + str;
#else
	return str;
#endif
}

void Game::createPlayer()
{
	Vector2f velocity(0,0);
	Vector2f position(0,0);
	Texture* texture = new Texture();
	texture->loadFromFile(resolvePath("PlayerSprite.png"));
	Rect<int> boundingBox((Vector2i)position, (Vector2i)texture->getSize());
	Sprite sprite(*texture, boundingBox);
	Player* player = new Player(velocity, position, boundingBox, sprite);
	entityList.push_back(player);
}

void Game::createBackground()
{
	Texture* t1 = new Texture();
	t1->loadFromFile(resolvePath("Sky.png"));
	Texture* t2 = NULL;
	Texture* t3 = NULL;
	background = new Background(t1, t2, t3);
}

void Game::createEnvironment(int x, int y, int xrep, int yrep)
{
	Vector2f velocity(0,0);
	Vector2f position(0,0);
	Texture* texture = new Texture();
	texture->loadFromFile(resolvePath("platform.jpg"));
	texture->setRepeated(true);
	Vector2i size = (Vector2i)texture->getSize();
	Rect<int> boundingBox(position.x,position.y,xrep*size.x,yrep*size.y);
	Sprite sprite(*texture, boundingBox);
	EnvironmentObject* obj1 = new EnvironmentObject(velocity, position, boundingBox, sprite);
	obj1->position = Vector2f(x,y);
	entityList.push_back(obj1);
}

std::vector<Entity*> Game::collide(Entity * entity)
{
	std::vector<Entity*> touching;
	for (Entity* other : entityList)
	{
		if (other != entity)
		{
			if (entity->boundingBox.intersects(other->boundingBox))
			{
				touching.push_back(other);
			}
		}
	}
	return touching;
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
	//And then there was time
	Clock clock;
	
	Clock fpsCounter;
	int framesThisSecond;
	
	// Start the game loop
    while (window->isOpen())
    {
		//Timing stuff
		float deltaTime = clock.getElapsedTime().asSeconds();
		clock.restart();
		
		if (DEVELOPER)
		{
			framesThisSecond++;
			
			if (fpsCounter.getElapsedTime().asSeconds() > 1) {
				fps.setString("FPS: " + std::to_string(framesThisSecond));
				framesThisSecond = 0;
				fpsCounter.restart();
			}
		}
		
        // Process events, if we have too many events here, then we need an event handler class or funciton or something
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
        window->clear(Color(255,255,255,255)); // background color = white
		
		//draw background before entities
		window->draw(*background);
		
		for (Entity* entity : entityList)
		{
			std::vector<Entity*> touching = collide(entity);
			entity->update(deltaTime, touching);
			window->draw(*entity);

		}
		
		if (DEVELOPER)
		{
			window->draw(fps);
		}
		
        // Update the window
        window->display();
    }
	
	cleanup();
}
