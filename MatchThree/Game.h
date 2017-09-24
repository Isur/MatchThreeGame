#pragma once
#include<SFML\Graphics.hpp>
#include "Gem.h"
#include "bgGem.h"
#include "settings.h"
#include "FgGem.h"
class Game
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	bool isMoving;
	bool isSwap;
	bool isMatch;
	bool game;
	bool start;
	bool done;
	int clicked;
	int score;
	int x0, x1, y0, y1, i, j;
	sf::Time sftime;
	sf::Clock clock;
	sf::Font font;
	sf::Text scoreText;
	sf::Text timeText;
	sf::Text gameOverText;
	sf::Text gameOverInfoText;
	Gem *gem[SIZE_X][SIZE_Y];
	bgGem *bg_Gem[SIZE_X][SIZE_Y];
	FgGem *fg_Gem[SIZE_X][SIZE_Y];

	sf::Vector2i offset;
	sf::Vector2i mousePosition;

	// METHODS
	bool finishGame();
	void swap(Gem *gem[][SIZE_Y], int x0, int y0, int x1, int y1);
	bool match(Gem *gem[][SIZE_Y], bgGem *bg_Gem[][SIZE_Y]);
	bool deleteAnimation(Gem *gem[][SIZE_Y]);
	void updateGrid(Gem *gem[][SIZE_Y]);
	void checkMoves();
	bool checkPosibleMove(Gem *gem[][SIZE_Y]);
	void setTexts();
	bool gameDone();
public:
	Game();
	~Game();

	// GETTERS

	// SETTERS

	// METHODS
	void prepareBoard();
	int events(sf::Event e, sf::RenderWindow &window);
	void drawing(sf::RenderWindow &window);
	bool gameEngine();

};

