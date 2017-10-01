#pragma once
#include <SFML\Graphics.hpp>
#include "settings.h"
#include "Game.h"
class Map
{
private:
	sf::View view;
	sf::Texture texture;
	sf::Texture mapLevel;
	sf::Sprite sprite;
	sf::Sprite circle[LEVELS];
	sf::Vector2f circlePosition[LEVELS];
	int posX;
	int posY;
	int direction;
	int done;

public:
	Map();
	~Map();

	int events(sf::Event e, sf::RenderWindow &window, Game *game);
	void drawMap(sf::RenderWindow &window);
	void move();
};

