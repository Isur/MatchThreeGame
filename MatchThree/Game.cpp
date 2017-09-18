#include "stdafx.h"
#include "Game.h"
#include <time.h>
#include <string> 
#include <stdlib.h>
#include <Windows.h>
#include "settings.h"
Game::Game()
{
	backgroundTexture.loadFromFile("images/background.png");
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
	prepareBoard();
	start = false;
}


Game::~Game()
{
}
// METHODS
void Game::checkStart()
{
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			if (bg_Gem[i][j]->getLevel() != 2) prepareBoard();
		}
	}
}
void Game::prepareBoard()
{
	int i, j, tempType;
	srand(time(NULL));
	sf::Vector2f position;
	sftime = sf::seconds(60);
	isMoving = false;
	isSwap = true;
	isMatch = false;
	game = true;
	clicked = 0;
	score = 0;
	start = false;
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			tempType = rand() % TYPES;
			position.x = offset.x + i*TILESIZE;
			position.y = offset.y + j*TILESIZE;
			bg_Gem[i][j] = new bgGem(true, position, 1);
			gem[i][j] = new Gem(true, position, tempType);
		}
	}
	
	
}
void Game::drawing(sf::RenderWindow &window)
{
	int i, j;
	window.clear();
	window.draw(backgroundSprite);
	if (game == false)
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
		}
	}
	window.display();
}
bool Game::finishGame()
{
	if (sftime <= sf::seconds(0))
	{
		game = false;
		sftime = sf::seconds(0);
		gameOverText.setString("GAME OVER");
		gameOverInfoText.setString("CLICK SPACE TO PLAY AGAIN");
	}
	else game = true;
	return game;
}
void Game::events(sf::Event e, sf::RenderWindow &window)
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
		}
}
bool Game::gameEngine()
{
	int points;
	sftime -= clock.getElapsedTime();
	if (clicked == 1 && game == true)
	{
		x0 = mousePosition.x / TILESIZE;
		y0 = mousePosition.y / TILESIZE;
		gem[x0][y0]->updateTextrue(true);
	}
	else if (clicked == 2)
	{
		start = true;
		x1 = mousePosition.x / TILESIZE;
		y1 = mousePosition.y / TILESIZE;
		if (abs(x0 - x1) + abs(y0 - y1) == 1)
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
	if (isMatch == true)
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
				if (bg_Gem[i][j]->getLevel() > 0 && start == true)
				{
					bg_Gem[i][j]->setLevel(bg_Gem[i][j]->getLevel() - 1);
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
void Game::updateGrid(Gem *gem[][SIZE_Y])
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
void Game::checkMoves()
{
	if (checkPosibleMove(gem) == false)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			if (gem[i][j]->getAlpha() > 10)
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
void Game::setTexts()
{
	timeText.setString("TIME: " + std::to_string((int)sftime.asSeconds()));
	scoreText.setString("SCORE: " + std::to_string(score));
}