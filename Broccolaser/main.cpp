#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"
#include "Game.h"

//This file ONLY knows about the window, it should not know anything about the game other than there is one to be run

using namespace sf;

int main(int, char const**)
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
    RenderWindow window(VideoMode(800, 600), "SFML window");
	
	//create the game object
	Game game(&window);
	
	game.run();
    
    return EXIT_SUCCESS;
}
