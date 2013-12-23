#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


#include "Game.h"

//This file runs the game and manages the window
//it should have no game logic

using namespace sf;

int main(int argc, char** arcv)
{
	
	/*
	 
	 some examples on how to use SFML

    // Set the Icon
    Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    Sprite sprite(texture);

    // Create a graphical text to display
    Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    Text text("Hello SFML", font, 50);
    text.setColor(Color::Black);

    // Load a music to play
    Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    //music.play();
	 */
	
	// Create the main window
    RenderWindow window(VideoMode(1280, 800), "SFML window");
	
	//create the game object
	Game game(&window);
	
	//in the future, this will be called by the menu
	game.setup();
	
	//run the game, its a myster what this does, at least as far as this file goes
	game.run();
    
    return EXIT_SUCCESS;
}
