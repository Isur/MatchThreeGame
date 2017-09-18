// MatchThree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "bgGem.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "MatchThree.h"
#include <string> 
#include<Windows.h>
#define SIZE_X 10
#define SIZE_Y 10
#define TYPES 7
#define TILESIZE 40
void swap(Gem *gem[][SIZE_Y], int x0, int y0, int x1, int y1);


bool checkPosibleMove(Gem *gem[][SIZE_Y])
{
	int i, j;
	int temp;
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			temp = gem[i][j]->getType();
			/*	DOWN	*/if (j < SIZE_Y - 3)
			{
				if (temp == gem[i][j + 1]->getType())
				{
					if (i == 0)
					{
						if (temp == gem[i][j + 3]->getType() || temp == gem[i + 1][j + 2]->getType()) return true;
					}
					else if (i == SIZE_X - 1)
					{
						if (temp == gem[i][j + 3]->getType() || temp == gem[i - 1][j + 2]->getType()) return true;
					}
					else
					{
						if (temp == gem[i][j + 3]->getType() || temp == gem[i - 1][j + 2]->getType() || temp == gem[i + 1][j + 2]->getType()) return true;
					}
				}
			}
			/*	UP		*/if (j > 2)
			{
				if (temp == gem[i][j - 1]->getType())
				{
					if (i == 0)
					{
						if (temp == gem[i][j - 3]->getType() || temp == gem[i + 1][j - 2]->getType()) return true;
					}
					else if (i == SIZE_X - 1)
					{
						if (temp == gem[i][j - 3]->getType() || temp == gem[i - 1][j - 2]->getType()) return true;
					}
					else
					{
						if (temp == gem[i][j - 3]->getType() || temp == gem[i - 1][j - 2]->getType() || temp == gem[i + 1][j - 2]->getType()) return true;
					}
				}

			}
			/*	RIGHT	*/if (i < SIZE_X - 3)
			{
				if (temp == gem[i + 1][j]->getType())
				{
					if (j == 0)
					{
						if (temp == gem[i + 3][j]->getType() || temp == gem[i + 2][j + 1]->getType()) return true;
					}
					else if (j == SIZE_Y - 1)
					{
						if (temp == gem[i + 3][j]->getType() || temp == gem[i + 2][j - 1]->getType()) return true;
					}
					else
					{
						if (temp == gem[i + 3][j]->getType() || temp == gem[i + 2][j - 1]->getType() || temp == gem[i + 2][j + 1]->getType()) return true;
					}
				}
			}
			/*	LEFT	*/if (i > 2) 
			{
				if (temp == gem[i - 1][j]->getType())
				{
					if (j == 0)
					{
						if (temp == gem[i - 3][j]->getType() || temp == gem[i - 2][j + 1]->getType()) return true;
					}
					else if (j == SIZE_Y - 1)
					{
						if (temp == gem[i - 3][j]->getType() || temp == gem[i - 2][j - 1]->getType()) return true;
					}
					else
					{
						if (temp == gem[i - 3][j]->getType() || temp == gem[i - 2][j + 1]->getType() || temp == gem[i - 2][j - 1]->getType()) return true;
					}
				}
			}
		}
	}
	return false;
}

bool deleteAnimation(Gem *gem[][SIZE_Y])
{
	int i, j;
	bool isMoving = false;
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{

			if (gem[i][j]->getType() == TYPES)
			{
				if (gem[i][j]->getAlpha() > 50)
				{
					gem[i][j]->setAlpha(gem[i][j]->getAlpha() - 40);
					isMoving = true;
				}
				else
				{
					gem[i][j]->setType(TYPES);
				}
			}
		}
	}
	return isMoving;
}

void updateGrid(Gem *gem[][SIZE_Y])
{
	int i, j;

	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			if (gem[i][j]->getType() == TYPES)
			{
				
				if (j == 0)
				{
					gem[i][j]->setType(rand() % TYPES);
					gem[i][j]->setAlpha(255);
				}
				else
				{
					gem[i][j]->setAlpha(255);
					swap(gem, i, j, i, j - 1);
				}
			}
		}
	}

}

int match(Gem *gem[][SIZE_Y], bgGem *bg_Gem[][SIZE_Y])
{
	int i, j,n; // TEMP
	int points = 0;
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			if (j != 0 && j != SIZE_Y - 1)
			{
				if (gem[i][j]->getType() != TYPES)
				if (gem[i][j - 1]->getType() == gem[i][j]->getType() && gem[i][j]->getType() == gem[i][j + 1]->getType())
				{
					for (n = j - 1; n <= j + 1; n++)
					{
						gem[i][n]->increaseMatch();
					}
				}
			}
			if (i != 0 && i != SIZE_X - 1)
			{
				if(gem[i][j]->getType() != TYPES)
				if (gem[i - 1][j]->getType() == gem[i][j]->getType() && gem[i][j]->getType() == gem[i + 1][j]->getType())
				{
					for (n = i - 1; n <= i + 1; n++)
					{
						gem[n][j]->increaseMatch();
					}
				}
			}
		}
	}
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			if (gem[i][j]->getMatch() > 0)
			{
				if (bg_Gem[i][j]->getLevel() > 0)
				{
					bg_Gem[i][j]->setLevel(bg_Gem[i][j]->getLevel() - 1);
				}
				gem[i][j]->setTypeNotSprite(TYPES);
				points += gem[i][j]->getMatch()*gem[i][j]->getValue();
				gem[i][j]->decreaseMatch();
				
			}
		}
	}
	return points;
}

void swap(Gem *gem[][SIZE_Y], int x0, int y0, int x1, int y1)
{
	gem[x0][y0]->setOldPosition(gem[x0][y0]->getPosition());
	gem[x1][y1]->setOldPosition(gem[x1][y1]->getPosition());
	

	gem[x0][y0]->setPosition(gem[x1][y1]->getOldPosition());
	gem[x1][y1]->setPosition(gem[x0][y0]->getOldPosition());
	
	Gem *temp;
	temp = gem[x0][y0];
	gem[x0][y0] = gem[x1][y1];
	gem[x1][y1] = temp;

}

int main()
{
	// SETTINGS
	sf::RenderWindow window(sf::VideoMode(550, 700), "Match 3 Game", sf::Style::Close);
	sf::Texture background_texture;
	background_texture.loadFromFile("images/background.png");
	sf::Sprite background_sprite;
	background_sprite.setTexture(background_texture);
	window.setFramerateLimit(60);
	int tileSize = TILESIZE;
	sf::Vector2i offset(66, 91);
	srand(time(NULL));
	// VARIABLES
	int i, j,n;	// temporary
	int tempType;	// temp for setting gem type
	bool isMoving = false, isSwap = true, isMatch = false, game = true;	// bools for animating / swapping / match / running game
	int clicked = 0; // clicking counter/ 0-1-2
	int x0, y0, x1, y1; // gems position
	int points, allPoints = 0; // for score
	sf::Time time = sf::seconds(60);	// time
	sf::Clock clock;		
	sf::Vector2f position;	// gem position
	sf::Vector2i mousePosition; // click position
	sf::Vector2f textPosition;	// position of text on screen
	textPosition.x = 100;
	textPosition.y = 600;
	sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Text score;
	score.setFont(font);
	score.setPosition(textPosition);
	sf::Text times;
	times.setFont(font);
	textPosition.y -= 50;
	times.setPosition(textPosition);
	sf::Text gameOver;
	gameOver.setFont(font);
	textPosition.y -= 50;
	gameOver.setPosition(textPosition);
	sf::Text gameOverText;
	gameOverText.setFont(font);
	textPosition.y = 50;
	gameOverText.setPosition(textPosition);
	gameOverText.setScale(sf::Vector2f(0.7f, 0.7f));
	// CREATE GEMS
	bgGem *bg_Gem[SIZE_X][SIZE_Y];
	Gem *gem[SIZE_X][SIZE_Y];
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			tempType = rand() % TYPES;
			position.x = offset.x + i*tileSize;
			position.y = offset.y + j*tileSize;
			bg_Gem[i][j] = new bgGem(true, position, 1);
			gem[i][j] = new Gem(true, position, tempType);
		}
	}

	while (window.isOpen())
	{
		// EVENTS
		sf::Event e;
		
		time -= clock.getElapsedTime();
		while (window.pollEvent(e))
		{

			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
			if (e.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::getPosition(window).x <= offset.x + tileSize*SIZE_X &&
					sf::Mouse::getPosition(window).y <= offset.y + tileSize*SIZE_Y &&
					sf::Mouse::getPosition(window).x > offset.x &&
					sf::Mouse::getPosition(window).y > offset.y)
				{
					if (isMoving == false) clicked++;
					mousePosition = sf::Mouse::getPosition(window) - offset;
				}
			}
			if (e.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					game = true;
					time = sf::seconds(60);
					for (i = 0; i < SIZE_X; i++)
					{
						for (j = 0; j < SIZE_Y; j++)
						{
							bg_Gem[i][j]->setLevel(2);
						}
					}
				}
			}
		}
		// FIRST CLICK
		if (clicked == 1 && game == true)
		{
			x0 = mousePosition.x / tileSize;
			y0 = mousePosition.y / tileSize;
			gem[x0][y0]->updateTextrue(true);
		}
		// SECOND CLICK
		else if (clicked == 2)
		{
			x1 = mousePosition.x / tileSize;
			y1 = mousePosition.y / tileSize;
			if (abs(x0 - x1) + abs(y0 - y1) == 1)	// if second one is up/down/left/right, not corner
			{
				swap(gem, x0,y0, x1,y1);
				points = match(gem, bg_Gem);
				if (points > 0) // if match, add time
				{
					time += sf::seconds(2);
					isSwap = true;
				}
				else isSwap = false;
				allPoints += points;	//score
				clicked = 0;
				gem[x0][y0]->updateTextrue(false);
				gem[x1][y1]->updateTextrue(false);
			}
			else
			{
				gem[x0][y0]->updateTextrue(false);
				clicked = 1;
			}
		}
	
		// FIND MATCH
		points = match(gem, bg_Gem);
		if (points > 0)
		{
			time += sf::seconds(1);
			isMatch = true;
		}
		allPoints += points;

		isMoving = false;
		// DELETE ANIMATION
		if (isMoving == false)
		{
			isMoving = deleteAnimation(gem);
		}
		// SWAP BACK IF NOT MATCH
		if (isSwap == false && isMoving == false)
		{
			swap(gem, x0, y0, x1, y1);
			isSwap = true;
		}

		// UPDATE
		if (isMoving == false)
		{
		 updateGrid(gem);
		}
		// CHECK MOVES
		if (checkPosibleMove(gem) == false && isMoving == false)
		{
			for (i = 0; i < SIZE_X; i++)
			{
				for (j = 0; j < SIZE_Y; j++)
				{
					if (gem[i][j]->getAlpha() > 10)
					{
						gem[i][j]->setAlpha(gem[i][j]->getAlpha() - 10);
						isMoving = true;
					}
					if(gem[i][j]->getAlpha() <= 10)
					{
						gem[i][j]->setType(rand() % TYPES);
					}
				}
			}
		}
		else
		{
			for (i = 0; i < SIZE_X; i++)
			{
				for (j = 0; j < SIZE_Y; j++)
				{
					if (gem[i][j]->getAlpha() < 255)
					{
						gem[i][j]->setAlpha(gem[i][j]->getAlpha() + 10);
					}
				}
			}
		}
		// TEXT
		std::string timer = "TIME: " + std::to_string((int)time.asSeconds());
		std::string scores = "SCORE: " + std::to_string(allPoints);
		score.setString(scores);
		times.setString(timer);
		clock.restart();
		// DRAWING
		window.clear();
		window.draw(background_sprite);
		if (time <= sf::seconds(0))
		{
			gameOver.setString("GAME OVER");
			gameOverText.setString("CLICK SPACE TO PLAY AGAIN");
			time = sf::seconds(0);
			game = false;
			window.draw(gameOver);
		}
		window.draw(gameOverText);
		window.draw(score);
		window.draw(times);
		for (i = 0; i < SIZE_X; i++)
		{
			for (j = 0; j < SIZE_Y; j++)
			{
				bg_Gem[i][j]->drawBgGem(window);
			}
		}	
		for (i = 0; i < SIZE_X; i++)
		{
			for (j = 0; j < SIZE_Y; j++)
			{
				gem[i][j]->drawGem(window);
			}
		}
		window.display();
	}

	return 0;
}