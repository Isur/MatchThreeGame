// MatchThree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "bgGem.h"
#include "Game.h"
#include "Menu.h"
#include "MatchThree.h"
#include "settings.h"

int main()
{
	// SETTINGS
	sf::RenderWindow window(sf::VideoMode(550, 700), "Match 3 Game", sf::Style::Close);
	window.setFramerateLimit(60);
	Game *game = new Game;
	Menu *menu = new Menu;
	bool play = false;

	while (window.isOpen())
	{

		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
			if (play == true) 
			{ 
				play = game->events(e, window); 
			}
			else
			{
				play = menu->events(e, window);
				if (play == true)
					game->prepareBoard();
			}
		}
		if (play == true)
		{
			play = game->gameEngine();
			game->drawing(window);
		}
		else
		{
			menu->drawText(window);
		}

	}

	return 0;
}