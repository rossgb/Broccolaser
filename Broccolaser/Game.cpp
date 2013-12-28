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
#include <SFML/Audio.hpp>
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
	
	createEnemy(800,400);
	
    music.openFromFile(resolvePath("voidboxleisureambient.ogg"));
	music.setLoop(true);
	music.setVolume(0.1);
	music.play();
	
	//window->setFramerateLimit(10);
	
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
	Texture* texture = new Texture();
	texture->loadFromFile(resolvePath("sprites.png"));
	//Rect<int> boundingBox(Vector2i(0,0), Vector2i(49,89));
	//Sprite sprite(*texture, Rect<int>(Vector2i(0,0),(Vector2i)texture->getSize()));

	player = new Player(Vector2f(0,0), texture);

	Texture* sword = new Texture();
	sword->loadFromFile(resolvePath("sword.png"));
	PlayerAttack* playerAttack = new PlayerAttack(player,sword);

	view = View(player->position, (Vector2f)(window->getSize()));
	camera = new Camera(player, &view);
	
	entityList.push_back(player);
	entityList.push_back(playerAttack);
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
	Texture* texture = new Texture();
	texture->loadFromFile(resolvePath("platform.jpg"));

	EnvironmentObject* obj1 = new EnvironmentObject(Vector2f(x,y), texture, Vector2i(xrep,yrep));
		
	entityList.push_back(obj1);
}

void Game::createEnemy(int x, int y)
{
	Texture* texture = new Texture();
	texture->loadFromFile(resolvePath("derp.png"));
	
	Enemy* enemy = new Enemy(Vector2f(x,y), texture, player);
	
	entityList.push_back(enemy);
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

void Game::run ()
{
	//And then there was time
	Clock fpsCounter;
	Clock deltaClock;
	int framesThisSecond;
	std::vector<Event> events;
	bool cameraOn = false;
	
	// Start the game loop
    while (window->isOpen())
    {
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
		events.clear();
        while (window->pollEvent(event))
        {
			events.push_back(event);
            // Close window : exit
            if (event.type == Event::Closed)
			{
                window->close();
            }
			
            // Escape pressed : exit
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
                //open menu
                window->close();
            }
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::C)
			{
                //toggle camera
				cameraOn = !cameraOn;
            }
        }
        // Clear screen
        window->clear(Color(255,255,255,255)); // background color = white
		
		//draw background before entities
		window->draw(*background);
		float deltaTime = deltaClock.restart().asSeconds();
		for (Entity* entity : entityList)
		{
			std::vector<Entity*> touching = collide(entity);
			entity->update(deltaTime, touching, events);
			window->draw(*entity);
			touching.clear();
		}
		
		if (cameraOn)
		{
			camera->update();
			window->setView(view);
		} else
		{
			window->setView(window->getDefaultView());
		}
		
		if (DEVELOPER)
		{
			window->draw(fps);
		}
		
        // Update the window
        window->display();
    }
}

Game::~Game()
{
	for (Entity* entity : entityList)
	{
		delete entity;
	}
	delete camera;
	delete background;
}
