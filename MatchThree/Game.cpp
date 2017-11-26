#include "stdafx.h"
#include "Game.h"
#include "Score.h"
#include "AboutLvl.h"
#include <time.h>
#include <string> 
#include <stdlib.h>
#include <Windows.h>
#include "settings.h"
#include <fstream>
#include <string>
#include <iostream>

Game::Game()
	:Windows()
{
	backgroundTexture.loadFromFile("images/bg.png");
	backgroundSprite.setTexture(backgroundTexture);
	font.loadFromFile("font.ttf");
	offset.x = OFFSET_X;
	offset.y = OFFSET_Y;
	timeText.setFont(font);
	timeText.setPosition(sf::Vector2f(100.0, 650.0));
	scoreText.setFont(font);
	scoreText.setPosition(sf::Vector2f(100.0, 600.0));
	gameOverText.setFont(font);
	gameOverText.setPosition(sf::Vector2f(300.0, 1.0));
	gameOverInfoText.setFont(font);
	gameOverInfoText.setPosition(sf::Vector2f(100.0, 1.0));
	start = false;

	gemBuffer.loadFromFile("sounds/gem_move_sound.wav");
	gemSound.setBuffer(gemBuffer);
	hammerBuffer.loadFromFile("sounds/hammer.wav");
	hammerSound.setBuffer(hammerBuffer);
	boomBuffer.loadFromFile("sounds/boom.wav");
	boomSound.setBuffer(boomBuffer);
	lightningBuffer.loadFromFile("sounds/lightning.wav");
	lightningSound.setBuffer(lightningBuffer);
	lavaBuffer.loadFromFile("sounds/lava.wav");
	lavaSound.setBuffer(lavaBuffer);

	music.openFromFile("sounds/level_music.wav");
	music.setLoop(true);
	music.setVolume(20);
	isPlaying = false;
}
Game::~Game()
{
}

void Game::stopMusic()
{
	music.stop();
	isPlaying = false;
}

// EVENTS
int Game::events(sf::Event e, sf::RenderWindow &window, Cursor *cursor)
{
	if (start == false)
	{
		start = about->events(e, window);
	}
	else
	{
		if (e.type == sf::Event::MouseMoved)
		{
			if (isSkill == true) cursor->setTexture(activeSkill);
			else cursor->setDefaultTexture();
		}
		if (e.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				for (i = 0; i < SIZE_X; i++)
				{
					for (j = 0; j < SIZE_X; j++)
					{
						gem[i][j]->updateTextrue(false);
					}
				}
				sf::Vector2i mp = sf::Mouse::getPosition(window);
				if (mp.x <= offset.x + TILESIZE*SIZE_X &&
					mp.y <= offset.y + TILESIZE*SIZE_Y &&
					mp.x > offset.x &&
					mp.y > offset.y)
				{
					mp -= offset;

					if (isSkill == true)
					{
						cursor->setTexture(activeSkill);
						x0 = mp.x / TILESIZE;
						y0 = mp.y / TILESIZE;

						if (activeSkill == 0)
						{
							gem[x0][y0]->updateTextrue(true);
						}
						else if (activeSkill == 1)
						{
							if (x0 > 0 && y0 > 0 && x0 < SIZE_X - 1 && y0 < SIZE_Y - 1)
							{
								for (int i = x0 - 1; i <= x0 + 1; i++)
								{
									for (int j = y0 - 1; j <= y0 + 1; j++)
									{
										gem[i][j]->updateTextrue(true);
									}
								}
							}
						}
						else if (activeSkill == 2)
						{
							int temp = gem[x0][y0]->getType();
							for (int i = 0; i < SIZE_X; i++)
							{
								for (int j = 0; j < SIZE_Y; j++)
								{
									if (gem[i][j]->getType() == temp)
									{
										gem[i][j]->updateTextrue(true);
									}
								}
							}
						}
						else if (activeSkill == 3)
						{
							for (int i = 0; i < SIZE_Y; i++)
							{
								gem[x0][i]->updateTextrue(true);
							}
						}
						else if (activeSkill == 4)
						{
							for (int i = 0; i < SIZE_X; i++)
							{
								gem[i][y0]->updateTextrue(true);
							}
						}
					}
					else
					{
						cursor->setDefaultTexture();
					}
				}
				else
				{
					cursor->setDefaultTexture();
					isSkill = false;
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				mousePosition = sf::Mouse::getPosition(window);
				for (int i = 0; i < 5; i++)
				{
					if (mousePosition.y > OFFSET_Y + SIZE_Y*TILESIZE + 10 && mousePosition.y < OFFSET_Y + SIZE_Y*TILESIZE + 10 + TILESIZE)
					{
						if (mousePosition.x > OFFSET_X + 2 * i*TILESIZE && mousePosition.x < OFFSET_X + 2 * i*TILESIZE + TILESIZE)
						{
							if (skill[i]->getQuantity() > 0 && start == true)
							{
								activeSkill = i;
								isSkill = true;
							}
							break;
						}
					}
				}
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
	}
	
	}
	if (e.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				prepareBoard(level);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				Score *scoreTable = new Score;
				scoreTable->checkIfTop(score);
				delete scoreTable;
				stopMusic();
				
				return 0;
			}
		}
	return 1;
}
// LOAD GAME
void Game::prepareBoard(int level)
{
	int i, j, tempType;	
	this->level = level;
	srand((unsigned int)time(NULL));
	sf::Vector2f position;
	// INITIAL SETTINGS
	isMoving = false;
	isSwap = true;
	isMatch = false;
	start = false;
	loading = false;
	done = false;
	game = true;
	isSkill = false;
	clicked = 0;
	score = 0;
	// SKILLS
	for (i = 0; i < 5; i++)
	{
		skill[i] = new Skills(i);
	}
	// LOAD SAVE / SCORE
	std::ifstream load;
	load.open("score/save.egg");
	load >> maxLevel;
	load >> score;
	load.close();
	std::string scoreLoad("score/");
	scoreLoad.append(std::to_string(level));
	scoreLoad.append(".egg");
	load.open(scoreLoad);
	load >> maxScore;
	load.close();
	
	// LOAD LEVEL
	std::ifstream fileLevel;
	std::string levelString("levels/");
	if(this->level <= 20) levelString.append(std::to_string(this->level));	
	else levelString.append("20");
	levelString.append(".egg");
	fileLevel.open(levelString);
	char levelChar[SIZE_X][SIZE_Y];
	for (i = 0; i < SIZE_Y; i++)
	{
		std::getline(fileLevel, levelString);
		for (j = 0; j < SIZE_X; j++)
		{
			levelChar[j][i] = levelString[j];
		}
	}
	std::getline(fileLevel, levelString);
	levelType = levelString;
	fileLevel.close();
	// CREATING LEVEL
	for (i = 0; i < SIZE_X; i++)
	{
		for (j = 0; j < SIZE_Y; j++)
		{
			// 1 - ONLY GEM
			// 2 - GEM WITH BACKGROUND
			// 3 - FROZEN GEM
			// 4 - FROZEN GEM WITH BACKGROUND
			tempType = rand() % TYPES;
			position.x = (float) offset.x + i*TILESIZE;
			position.y = (float) offset.y + j*TILESIZE;

			gem[i][j] = new Gem(position, tempType);
			switch (levelChar[i][j])
			{
			case '1':
				bg_Gem[i][j] = new bgGem(position, 0, 0);
				fg_Gem[i][j] = new FgGem(1, position, 0);
				break;
			case '2':
				bg_Gem[i][j] = new bgGem(position, 1, 2);
				fg_Gem[i][j] = new FgGem(1, position, 0);
				break;
			case '3':
				bg_Gem[i][j] = new bgGem(position, 0, 0);
				fg_Gem[i][j] = new FgGem(1, position, 2);
				break;
			case '4':
				bg_Gem[i][j] = new bgGem(position, 1, 2);
				fg_Gem[i][j] = new FgGem(1, position, 2);
				break;

			}
			gem[i][j]->setAlpha(0);
			bg_Gem[i][j]->setAlpha(0);
			fg_Gem[i][j]->setAlpha(0);
		}
	}	
	for (int i = 0; i < 5; i++)
	{
		oldScore[i] = 0;
	}
	about = new AboutLvl(levelType, level);
	loading = false;
	sftime = sf::seconds(60);
}
//ENGINE
bool Game::gameEngine()
{
	if (start == false || loading == false)
	{
		for (i = 0; i < SIZE_X; i++)
		{
			for (j = 0; j < SIZE_Y; j++)
			{
				if (gem[i][j]->getAlpha() < 255)
				{
					gem[i][j]->setAlpha(gem[i][j]->getAlpha() + 5);
					bg_Gem[i][j]->setAlpha(gem[i][j]->getAlpha() + 5);
					fg_Gem[i][j]->setAlpha(gem[i][j]->getAlpha() +5);
					
				}
				else
				{
					loading = true;
					
				}
			}
		}
		
	}
	std::cout << "status: " << start << " & " << std::to_string(sftime.asSeconds()) << std::endl;
	if (loading == true)
	{

		if(start == true) if (clock.getElapsedTime() < sf::seconds(1)) sftime -= clock.getElapsedTime();
		if (mousePosition.x <= TILESIZE*SIZE_X &&
			mousePosition.y <= TILESIZE*SIZE_Y &&
			mousePosition.x > 0 &&
			mousePosition.y > 0)
		{
			if (isSkill == true)
			{
				x0 = mousePosition.x / TILESIZE;
				y0 = mousePosition.y / TILESIZE;
				useSkill();
				clicked = 0;
				for (i = 0; i < SIZE_X; i++)
				{
					for (j = 0; j < SIZE_X; j++)
					{
						gem[i][j]->updateTextrue(false);
					}
				}
			}
			else if (clicked == 1 && game == true && isMoving == false)
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
				x1 = mousePosition.x / TILESIZE;
				y1 = mousePosition.y / TILESIZE;

				if (abs(x0 - x1) + abs(y0 - y1) == 1 && fg_Gem[x1][y1]->getLevel() == 0 && gem[x1][y1]->getType() != TYPES)
				{
					swap(gem, x0, y0, x1, y1);
					if (match(gem, bg_Gem) == true)
					{
						sftime += sf::seconds(2);
						isSwap = true;
						gemSound.play();
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
		}

		isMatch = false;
		isMatch = match(gem, bg_Gem);
		if (isMatch == true && start == true)
		{
			sftime += sf::seconds(1);
		}
		isMoving = false;
		if (isMoving == false && start == true)
		{
			isMoving = deleteAnimation(gem);
		}
		if (isSwap == false && isMoving == false)
		{
			swap(gem, x0, y0, x1, y1);
			isSwap = true;
		}
		if (isMoving == false && done == false && start == true)
		{
			updateGrid(gem);
			skills();
		}
		else if (done == true)
		{
			for (i = 0; i < SIZE_X; i++)
			{
				for (j = 0; j < SIZE_Y; j++)
				{
					if (gem[i][j]->getAlpha() > 5)
					{
						gem[i][j]->setAlpha(gem[i][j]->getAlpha() - 5);
						isMoving = true;
					}
				}
			}
			if (gem[SIZE_X - 1][SIZE_Y - 1]->getAlpha() <= 10)
			{
				this->level++;
				prepareBoard(level);
			}
		}
		if (isMoving == false)
		{
			checkMoves();
		}

		setTexts();

		clock.restart();

	}
		return finishGame();
	
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
		music.stop();
		isPlaying = false;
	}
	else game = true;
	return game;
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
				if(start == true) score += gem[i][j]->getValue();
				if (bg_Gem[i][j]->getLevel() > 0 && start == true && fg_Gem[i][j]->getLevel() == 0)
				{
					bg_Gem[i][j]->setLevel(bg_Gem[i][j]->getLevel() - 1);
				}
				if (fg_Gem[i][j]->getLevel() > 0 && start == true)
				{
					fg_Gem[i][j]->setLevel(fg_Gem[i][j]->getLevel() - 1);

				}
				if(fg_Gem[i][j]->getLevel() == 0) gem[i][j]->setTypeNotSprite(TYPES);
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

	if (done == false)
	{
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
						if (fg_Gem[i][j - 1]->getLevel() == 0 && fg_Gem[i][j]->getLevel() == 0)
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
	else if(done == false)
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
bool Game::gameDone()
{
	if (levelType == "points")
	{
		if (score < 2500*level) return false;
	}
	else if (levelType == "ice")
	{
		for (int i = 0; i < SIZE_X; i++)
		{
			for (int j = 0; j < SIZE_Y; j++)
			{
				if (fg_Gem[i][j]->getLevel() > 0)
				{
					return false;
				}
			}
		}
	}
	else if(levelType == "background")
	{
		for (int i = 0; i < SIZE_X; i++)
		{
			for (int j = 0; j < SIZE_Y; j++)
			{
				if (bg_Gem[i][j]->getLevel() > 0)
				{
					return false;
				}
			}
		}
	}
	else if (levelType == "all")
	{
		for (int i = 0; i < SIZE_X; i++)
		{
			for (int j = 0; j < SIZE_Y; j++)
			{
				if (bg_Gem[i][j]->getLevel() > 0  || fg_Gem[i][j]->getLevel() > 0)
				{
					return false;
				}
			}
		}
	}
	
	// SAVE SCORE / LEVEL
	std::ofstream save;
	save.open("score/save.egg");
	if(level > maxLevel) save << level << std::endl;
	else save << maxLevel << std::endl;
	save.close();
	std::ofstream saveScore;
	std::string scoreFile("score/");
	scoreFile.append(std::to_string(level));
	scoreFile.append(".egg");
	saveScore.open(scoreFile);
	if (score > maxScore) saveScore << score;
	else saveScore << maxScore;
	saveScore.close();
	Score *scoreTable = new Score;
	scoreTable->checkIfTop(score);
	delete scoreTable;
	
	return true;
}
void Game::skills()
{
	if (score == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			oldScore[i] = 0;
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if (score > oldScore[i] + 1000 * (i + 1)) { skill[i]->setQuantity(skill[i]->getQuantity() + 1); oldScore[i] = score; }
		}
	}

}
void Game::useSkill()
{
	if (activeSkill == 0)
	{
		gem[x0][y0]->increaseMatch();
		skill[0]->setQuantity(skill[0]->getQuantity() - 1);
		isSkill = false;
		hammerSound.play();
	}
	if (activeSkill == 1)
	{
		if (x0 > 0 && y0 > 0 && x0 < SIZE_X - 1 && y0 < SIZE_Y - 1)
		{
			for (int i = x0 - 1; i <= x0 + 1; i++)
			{
				for (int j = y0 - 1; j <= y0 + 1; j++)
				{
					gem[i][j]->increaseMatch();
				}
			}
			skill[1]->setQuantity(skill[1]->getQuantity() - 1);
			isSkill = false;
			boomSound.play();
		}
	}
	if (activeSkill == 2)
	{
		int temp = gem[x0][y0]->getType();
		for (int i = 0; i < SIZE_X; i++)
		{
			for (int j = 0; j < SIZE_Y; j++)
			{
				if (gem[i][j]->getType() == temp)
				{
					gem[i][j]->increaseMatch();
				}
			}
		}
		skill[2]->setQuantity(skill[2]->getQuantity() - 1);
		isSkill = false;
		lightningSound.play();
	}
	if (activeSkill == 3)
	{
		for (int i = 0; i < SIZE_Y; i++)
		{
			gem[x0][i]->increaseMatch();
		}
		skill[3]->setQuantity(skill[3]->getQuantity() - 1);
		isSkill = false;
		lavaSound.play();
	}
	if (activeSkill == 4)
	{
		for (int i = 0; i < SIZE_X; i++)
		{
			gem[i][y0]->increaseMatch();
		}
		skill[4]->setQuantity(skill[4]->getQuantity() - 1);
		isSkill = false;
		lavaSound.play();
	}
	

}
// DRAW
void Game::setTexts()
{
	timeText.setString("TIME: " + std::to_string((int)sftime.asSeconds()));
	scoreText.setString("SCORE: " + std::to_string(score));
	if (done == true)
	{
		gameOverText.setString("DONE!");
	}
	gameOverInfoText.setString("LEVEL: " + std::to_string(level) + "\nHIGH SCORE: " + std::to_string(maxScore));
}
void Game::drawing(sf::RenderWindow &window)
{
	int i, j;
	window.draw(backgroundSprite);
	for (i = 0; i < 5; i++)
	{
		skill[i]->drawSkills(window);
	}
	if (done == true)
	{
		window.draw(gameOverText);
	}
	window.draw(gameOverInfoText);
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
	if (start == false && game == true) about->drawAboutLvl(window);
	if (!isPlaying && game) { music.play(); isPlaying = true; }
}