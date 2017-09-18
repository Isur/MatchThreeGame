// MatchThree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "bgGem.h"
#include "Game.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "MatchThree.h"
#include <string> 
#include<Windows.h>
#include "settings.h"

int main()
{
	// SETTINGS
	sf::RenderWindow window(sf::VideoMode(550, 700), "Match 3 Game", sf::Style::Close);
	window.setFramerateLimit(60);
	Game *game = new Game;
	bool play = true;
	game->prepareBoard();
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
				game->events(e, window); 
			}
		}
		if (play == true)
		{
			play = game->gameEngine();
			game->drawing(window);
		}

	}

	return 0;
}