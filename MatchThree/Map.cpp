#include "stdafx.h"
#include "Map.h"
#include <fstream>
Map::Map()
{
	view.reset(sf::FloatRect(0, 0, 550, 700));
	texture.loadFromFile("images/map.png");
	mapLevel.loadFromFile("images/mapLevel.png");
	sprite.setTexture(texture);

	circlePosition[0] = sf::Vector2f(279, 337);
	circlePosition[1] = sf::Vector2f(358, 326);
	circlePosition[2] = sf::Vector2f(422, 387);
	circlePosition[3] = sf::Vector2f(470, 444);
	circlePosition[4] = sf::Vector2f(527, 375);
	circlePosition[5] = sf::Vector2f(561, 307);
	circlePosition[6] = sf::Vector2f(627, 285);
	circlePosition[7] = sf::Vector2f(706, 306);
	circlePosition[8] = sf::Vector2f(786, 323);
	circlePosition[9] = sf::Vector2f(862, 312);
	circlePosition[10] = sf::Vector2f(933, 301);
	circlePosition[11] = sf::Vector2f(1035, 305);
	circlePosition[12] = sf::Vector2f(1090, 269);
	circlePosition[13] = sf::Vector2f(1139, 211);
	circlePosition[14] = sf::Vector2f(1175, 273);
	circlePosition[15] = sf::Vector2f(1260, 306);
	circlePosition[16] = sf::Vector2f(1283, 418);
	circlePosition[17] = sf::Vector2f(1392, 441);
	circlePosition[18] = sf::Vector2f(1288, 524);
	circlePosition[19] = sf::Vector2f(1288, 602);


	for (int i = 0; i < 20; i++)
	{
		circle[i].setTexture(mapLevel);
		if( i < done-1) circle[i].setTextureRect(sf::IntRect(0, 0, 24, 24));
		else  circle[i].setTextureRect(sf::IntRect(48, 0, 24, 24));
		circle[i].setPosition(circlePosition[i]);
	}
	
	posX = 0;
	posY = 0;

}


Map::~Map()
{
}

void Map::move()
{
	if (direction == 0)
	{
		;
	}
	else if (direction == 1)
	{
		if (posX < (texture.getSize().x - view.getSize().x) / SHIFT - 1)
		{
			view.move(SHIFT, 0);
			posX++;
		}
	}
	else if (direction == 2)
	{
		if (posX > 0)
		{
			view.move(-SHIFT, 0);
			posX--;
		}
	}
	else if (direction == 3)
	{
		view.move(0, SHIFT);
	}
	else if (direction == 4)
	{
		view.move(0, -SHIFT);
	}

}

int Map::events(sf::Event e, sf::RenderWindow &window, Game *game)
{
	sf::Vector2f moved;
	if (e.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return 0;
		}
	}
	if (e.type == sf::Event::MouseMoved)
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		if (pos.x > 500 && pos.x < 550)
		{
			direction = 1;
		}
		else if (pos.x < 50 && pos.x > 0)
		{
			direction = 2;
		}
		else { direction = 0; }
		for (int i = 0; i < LEVELS; i++)
		{

			if (pos.x > circlePosition[i].x - posX * SHIFT && pos.x < circlePosition[i].x + 24 - posX * SHIFT)
			{
				if (pos.y > circlePosition[i].y - posY*SHIFT && pos.y < circlePosition[i].y + 24 - posY * SHIFT)
				{
					if(i > done-1) circle[i].setTextureRect(sf::IntRect(24,0,24,24));
					else circle[i].setTextureRect(sf::IntRect(72, 0, 24, 24));
				}
				else
				{
					if(i > done-1) circle[i].setTextureRect(sf::IntRect(0, 0, 24, 24));
					else circle[i].setTextureRect(sf::IntRect(48, 0, 24, 24));
				}

			}
			else 
			{ 
				if (i > done-1) circle[i].setTextureRect(sf::IntRect(0, 0, 24, 24));
				else circle[i].setTextureRect(sf::IntRect(48, 0, 24, 24));
			}
		}
	}
	if (e.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		for (int i = 0; i < LEVELS; i++)
		{

			if (pos.x > circlePosition[i].x - posX * SHIFT && pos.x < circlePosition[i].x + 24 - posX * SHIFT)
			{
				if (pos.y > circlePosition[i].y - posY*SHIFT && pos.y < circlePosition[i].y + 24 - posY * SHIFT)
				{
					if (done >= i)
					{
						game->prepareBoard(i + 1);
						return 1;
					}
				}
			}
		}
	}
	return 4;
}

void Map::drawMap(sf::RenderWindow &window)
{
	std::ifstream save;
	save.open("score/save.egg");
	save >> done;
	save.close();
	if (done < 0) done = 0;
	
	window.setView(view);
	window.draw(sprite);

	for(int i = 0; i < LEVELS; i++) window.draw(circle[i]);
}
