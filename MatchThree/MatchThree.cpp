// MatchThree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "bgGem.h"
#include "Game.h"
#include "Menu.h"
#include "Score.h"
#include "Help.h"
#include "MatchThree.h"
#include "settings.h"

void deleteObjects(Game *game, Menu *menu, Score *score, Help *help)
{
	delete game;
	delete menu;
	delete score;
	delete help;
}

int main()
{
	// SETTINGS
	sf::RenderWindow window(sf::VideoMode(550, 700), "Match 3 Game", sf::Style::Close);
	window.setFramerateLimit(60);
	Menu *menu = new Menu;
	Game *game = new Game;
	Score *score = new Score;
	Help *help = new Help;
	
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
			switch (frame)
			{
			case 0:
				frame = menu->events(e, window);
				if (frame == 1)
				{
					game->prepareBoard(1);
				}
				break;
			case 1:
				frame = game->events(e, window);
				break;
			case 2:
				frame = score->events(e, window);
				break;
			case 3:
				frame = help->events(e, window);
			default:
				break;

			}
		}
		switch (frame)
		{
		case 0:
			if(menu) menu->drawMenu(window);
			break;
		case 1:
			play = game->gameEngine();
			if (play) frame = 1;
			else frame = 0;
			game->drawing(window);
			break;
		case 2:
			score->drawScore(window);
			break;
		case 3:
			help->drawHelp(window);
			break;
		default:
			break;
		}




	}

	return 0;
}