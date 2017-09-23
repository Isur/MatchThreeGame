// MatchThree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "bgGem.h"
#include "Game.h"
#include "Menu.h"
#include "Score.h"
#include "MatchThree.h"
#include "settings.h"

int main()
{
	// SETTINGS
	sf::RenderWindow window(sf::VideoMode(550, 700), "Match 3 Game", sf::Style::Close);
	window.setFramerateLimit(60);
	Game *game = new Game;
	Menu *menu = new Menu;
	Score *score = new Score;
	int frame = 0;
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
			if (frame == 1) 
			{ 
				frame = game->events(e, window); 
			}
			else if(frame == 0)
			{
				frame = menu->events(e, window);
				if (frame == 1)
				{
					game->prepareBoard();
				}
			}
			else if (frame == 2)
			{
				
			}
		}
		if (frame == 1)
		{
			play = game->gameEngine();
			if (play) frame = 1;
			else frame = 0;
			game->drawing(window);
		}
		else if(frame == 0)
		{
			menu->drawMenu(window);
		}
		else if (frame == 2)
		{
			score->drawScore(window);
		}

	}

	return 0;
}