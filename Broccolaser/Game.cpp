//
//  Game.cpp
//  Broccolaser
//
//  Created by Ross Gordon-Baker on 2013-12-18.
//
// The game class will be the go-between from game knowledge to screen knowledge
// it will include sfml stuff as well as game objects.
// draw loop happens here
// contains a list of drawables

#include <SFML/Graphics.hpp>

#include "Game.h"

Game::Game(RenderWindow* w)
{
	window = w;
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
            if (event.type == Event::Closed) {
                window->close();
            }
			
            // Espace pressed : exit
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window->close();
            }
        }
		
        // Clear screen
        window->clear();
		
        // Update the window
        window->display();
    }
}
