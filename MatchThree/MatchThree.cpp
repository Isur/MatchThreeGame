// MatchThree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "bgGem.h"
#include "Game.h"
#include "Menu.h"
#include "Cursor.h"
#include "Score.h"
#include "Help.h"
#include "MatchThree.h"
#include "Map.h"
#include "settings.h"

int main()
{
	// SETTINGS
	sf::RenderWindow window(sf::VideoMode(550, 700), "Match 3 Game", sf::Style::Close);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);
	Menu *menu = new Menu;
	Game *game = new Game;
	Score *score = new Score;
	Help *help = new Help;
	Cursor *cursor = new Cursor;
	Map *map = new Map;
	int frame = 0;
	/*
		0 - MENU
		1 - GAME
		2 - SCORE
		3 - HELP
		4 - MAP
	*/
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
			if (e.type == sf::Event::MouseMoved)
			{
				cursor->move(sf::Mouse::getPosition(window));
				
			}
			switch (frame)
			{
			case 0:
				frame = menu->events(e, window);
				break;
			case 1:
				frame = game->events(e, window, cursor);
				break;
			case 2:
				frame = score->events(e, window);
				break;
			case 3:
				frame = help->events(e, window);
				break;
			case 4:
				frame = map->events(e, window, game);
				break;
			default:
				break;

			}
		}
		window.clear();
		
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
		case 4:
			map->drawMap(window);
			map->move();
		default:
			break;
		}
		

		cursor->drawCursor(window);
		window.display();

	}

	return 0;
}