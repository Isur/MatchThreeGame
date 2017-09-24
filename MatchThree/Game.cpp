#include "stdafx.h"
#include "Game.h"
#include "Score.h"
#include <time.h>
#include <string> 
#include <stdlib.h>
#include <Windows.h>
#include "settings.h"
Game::Game()
{
	backgroundTexture.loadFromFile("images/bg.png");
	backgroundSprite.setTexture(backgroundTexture);
	font.loadFromFile("font.ttf");
	offset.x = OFFSET_X;
	offset.y = OFFSET_Y;
	timeText.setFont(font);
	timeText.setPosition(sf::Vector2f(100.0, 600.0));
	scoreText.setFont(font);
	scoreText.setPosition(sf::Vector2f(100.0, 550.0));
	gameOverText.setFont(font);
	gameOverText.setPosition(sf::Vector2f(100.0, 500.0));
	gameOverInfoText.setFont(font);
	gameOverInfoText.setPosition(sf::Vector2f(100.0, 50.0));
	start = false;
	prepareBoard();
}
Game::~Game()
{
}
// METHODS

void Game::prepareBoard()
{
	int i, j, tempType;
	srand(time(NULL));
	sf::Vector2f position;
	isMoving = false;
	isSwap = true;
	isMatch = false;
	game = true;
	clicked = 0;
	score = 0;
	start = false;
	done = false;
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			tempType = rand() % TYPES;
			position.x = offset.x + i*TILESIZE;
			position.y = offset.y + j*TILESIZE;
			bg_Gem[i][j] = new bgGem(true, position, 1);
			gem[i][j] = new Gem(true, position, tempType);
			if(j == 4)	fg_Gem[i][j] = new FgGem(true, 1, position, 2);
			else fg_Gem[i][j] = new FgGem(true, 1, position, 0);
		}
	}
	
	sftime = sf::seconds(60);
	
}
void Game::drawing(sf::RenderWindow &window)
{
	int i, j;
	window.clear();
	window.draw(backgroundSprite);
	if (done == true)
	{
		window.draw(gameOverText);
		window.draw(gameOverInfoText);
	}
	window.draw(scoreText);
	window.draw(timeText);
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			bg_Gem[i][j]->drawBgGem(window);
			gem[i][j]->drawGem(window);
			fg_Gem[i][j]->drawFgGem(window);
		}
	}
	window.display();
}
bool Game::finishGame()
{
	if (sftime <= sf::seconds(0))
	{
		game = false;
		start = false;
		sftime = sf::seconds(0);
		Score *scoreTable = new Score;
		scoreTable->checkIfTop(score);
		delete scoreTable;
	}
	else game = true;
	return game;
}
int Game::events(sf::Event e, sf::RenderWindow &window)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		mousePosition = sf::Mouse::getPosition(window);
		if (mousePosition.x <= offset.x + TILESIZE*SIZE_X &&
			mousePosition.y <= offset.y + TILESIZE*SIZE_Y &&
			mousePosition.x > offset.x &&
			mousePosition.y > offset.y)
		{
			if (isMoving == false)
			{
				clicked++;
			}
			mousePosition -= offset;
		}
	}
	if (e.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				prepareBoard();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				Score *scoreTable = new Score;
				scoreTable->checkIfTop(score);
				delete scoreTable;
				return 0;
			}
		}
	return 1;
}
bool Game::gameEngine()
{
	int points;
	if(start == true) sftime -= clock.getElapsedTime();
	if (clicked == 1 && game == true && isMoving == false)
	{
		x0 = mousePosition.x / TILESIZE;
		y0 = mousePosition.y / TILESIZE;
		if (fg_Gem[x0][y0]->getLevel() > 0 || gem[x0][y0]->getType() == TYPES)
		{
			clicked = 0;
		}
		else 
		{
			gem[x0][y0]->updateTextrue(true);
		}
	}
	else if (clicked == 2 && isMoving == false)
	{
		start = true;
		x1 = mousePosition.x / TILESIZE;
		y1 = mousePosition.y / TILESIZE;

		if (abs(x0 - x1) + abs(y0 - y1) == 1 && fg_Gem[x1][y1]->getLevel() == 0 && gem[x1][y1]->getType() != TYPES)
		{
			swap(gem, x0, y0, x1, y1); 
			if(match(gem, bg_Gem) == true)
			{
				sftime += sf::seconds(2);
				isSwap = true;
			}
			else isSwap = false;
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
	isMatch = false;
	isMatch = match(gem,bg_Gem);
	if (isMatch == true && start == true)
	{
		sftime += sf::seconds(1);
	}
	isMoving = false;
	if (isMoving == false)
	{
		isMoving = deleteAnimation(gem);
	}
	if (isSwap == false && isMoving == false)
	{
		swap(gem, x0, y0, x1, y1);
		isSwap = true;
	}
	if (isMoving == false)
	{
		updateGrid(gem);
	}
	if (isMoving == false)
	{
		checkMoves();
	}

	setTexts();
	clock.restart();
	return finishGame();
}
void Game::swap(Gem *gem[][SIZE_Y], int x0, int y0, int x1, int y1)
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
bool Game::match(Gem *gem[][SIZE_Y], bgGem *bg_Gem[][SIZE_Y])
{
	int i, j, n;
	bool match = false;
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
							match = true;
						}
					}
			}
			if (i != 0 && i != SIZE_X - 1)
			{
				if (gem[i][j]->getType() != TYPES)
					if (gem[i - 1][j]->getType() == gem[i][j]->getType() && gem[i][j]->getType() == gem[i + 1][j]->getType())
					{
						for (n = i - 1; n <= i + 1; n++)
						{
							gem[n][j]->increaseMatch();
							match = true;
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
				score += gem[i][j]->getValue();
				if (bg_Gem[i][j]->getLevel() > 0 && start == true && fg_Gem[i][j]->getLevel() == 0)
				{
					bg_Gem[i][j]->setLevel(bg_Gem[i][j]->getLevel() - 1);
				}
				if (fg_Gem[i][j]->getLevel() > 0 && start == true)
				{
					fg_Gem[i][j]->setLevel(fg_Gem[i][j]->getLevel() - 1);

				}
				
				gem[i][j]->setTypeNotSprite(TYPES);
				gem[i][j]->decreaseMatch();
				
			}
		}
	}
	
	return match;
}
bool Game::deleteAnimation(Gem *gem[][SIZE_Y])
{
	int i, j;
	bool isMoving = false;
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			if (gem[i][j]->getType() == TYPES && gem[i][j]->getUnderBlock() == false)
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
void Game::updateGrid(Gem *gem[][SIZE_Y])
{
	int i, j;
	done = gameDone();
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
					if (fg_Gem[i][j - 1]->getLevel() == 0)
					{
						gem[i][j]->setAlpha(255);
						swap(gem, i, j, i, j - 1);
					}
					else
					{
						gem[i][j]->setUnderBlock(true);
					}
				}
			}
		}
	}

}
void Game::checkMoves()
{
	if (checkPosibleMove(gem) == false)
	{
		for(i = 0; i < SIZE_X; i++)
		for (j = 0; j < SIZE_Y; j++)
		{
			if (gem[i][j]->getAlpha() > 10 && gem[i][j]->getType() != TYPES)
			{
				gem[i][j]->setAlpha(gem[i][j]->getAlpha() - 10);
				isMoving = true;
			}
			if (gem[i][j]->getAlpha() <= 10)
			{
				gem[i][j]->setType(rand() % TYPES);
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
}
bool Game::checkPosibleMove(Gem *gem[][SIZE_Y])
{
	int i, j;
	int temp;
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			temp = gem[i][j]->getType();
			if (fg_Gem[i][j]->getLevel() == 0 && temp != TYPES)
			{
				/* DOWN */ 
				if(j <= SIZE_Y-2)
				if (fg_Gem[i][j + 1]->getLevel() == 0 && gem[i][j+1]->getType() != TYPES)
				{
					if (j <= SIZE_Y - 4) { if (temp == gem[i][j + 2]->getType() && temp == gem[i][j + 3]->getType()) { return true; } }
					if (i >= 2) { if (temp == gem[i - 1][j + 1]->getType() && temp == gem[i - 2][j + 1]->getType()) { return true; } }
					if (i <= SIZE_X - 3) { if (temp == gem[i + 1][j + 1]->getType() && temp == gem[i + 2][j + 1]->getType()) { return true; } }
					if (i >= 1 && i <= SIZE_X - 2) { if (temp == gem[i + 1][j + 1]->getType() && temp == gem[i - 1][j + 1]->getType()) { return true; } }
				}

				/* UP */
				if(j >= 1)
				if (fg_Gem[i][j - 1]->getLevel() == 0 && gem[i][j - 1]->getType() != TYPES)
				{
					if (j >= 3) { if (temp == gem[i][j - 2]->getType() && temp == gem[i][j - 3]->getType()) { return true; } }
					if (i >= 2) { if (temp == gem[i - 1][j - 1]->getType() && temp == gem[i - 2][j - 1]->getType()) { return true; } }
					if (i <= SIZE_X - 3) { if (temp == gem[i + 1][j - 1]->getType() && temp == gem[i + 2][j - 1]->getType()) { return true; } }
					if (i >= 1 && i <= SIZE_X - 2) { if (temp == gem[i + 1][j - 1]->getType() && temp == gem[i - 1][j - 1]->getType()) { return true; } }
				}

				/* RIGHT */
				if(i <= SIZE_X - 2)
				if (fg_Gem[i + 1][j]->getLevel() == 0 && gem[i + 1][j]->getType() != TYPES)
				{
					if (i <= SIZE_X - 4) { if (temp == gem[i + 2][j]->getType() && temp == gem[i + 3][j]->getType()) { return true; } }
					if (j <= SIZE_Y - 3) { if (temp == gem[i + 1][j + 1]->getType() && temp == gem[i + 1][j + 2]->getType()) { return true; } }
					if (j >= 2) { if (temp == gem[i + 1][j - 1]->getType() && temp == gem[i + 1][j - 2]->getType()) { return true; } }
					if (j >= 1 && j <= SIZE_Y - 2) { if (temp == gem[i + 1][j + 1]->getType() && temp == gem[i + 1][j - 1]->getType()) { return true; } }
				}
				/* LEFT */	
				if(i >= 1)
				if (fg_Gem[i - 1][j]->getLevel() == 0 && gem[i - 1][j]->getType() != TYPES)
				{
					if (i >= 3) { if (temp == gem[i - 2][j]->getType() && temp == gem[i - 3][j]->getType()) { return true; } }
					if (j <= SIZE_Y - 3) { if (temp == gem[i - 1][j + 1]->getType() && temp == gem[i - 1][j + 2]->getType()) { return true; } }
					if (j >= 2) { if (temp == gem[i - 1][j - 1]->getType() && temp == gem[i - 1][j - 2]->getType()) { return true; } }
					if (j >= 1 && j <= SIZE_Y - 2) { if (temp == gem[i - 1][j + 1]->getType() && temp == gem[i - 1][j - 1]->getType()) { return true; } };
				}
			} 
			
		}
	}
	return false;
}
void Game::setTexts()
{
	timeText.setString("TIME: " + std::to_string((int)sftime.asSeconds()));
	scoreText.setString("SCORE: " + std::to_string(score));
	if (done == true)
	{
		gameOverText.setString("DONE!");
		gameOverInfoText.setString("YOU CAN PLAY KEEP PLAYING!");
	}
}
bool Game::gameDone()
{
	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; i < SIZE_Y; j++)
		{
			if (bg_Gem[i][j]->getLevel() != 0)
			{
				return false;
			}
		}
	}
	return true;
}