#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include "Gem.h"
#include "bgGem.h"
#include "settings.h"
#include "FgGem.h"
#include "Windows.h"
#include "Skills.h"
#include "Object.h"
#include "Cursor.h"
#include "AboutLvl.h"
class Game:public Windows
{
private:

	bool isMoving;
	bool isSwap;
	bool isMatch;
	bool game;
	bool start;
	bool done;
	bool loading;
	int clicked;
	int score;
	int oldScore[5];
	int maxScore;
	int x0, x1, y0, y1, i, j;
	int level;
	int maxLevel;
	int activeSkill;
	bool isSkill;
	std::string levelType;
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
	Skills *skill[5];
	AboutLvl* about;

	sf::Vector2i offset;
	sf::Vector2i mousePosition;

	sf::Music music;
	bool isPlaying;

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
	void skills();
	void useSkill();
	void stopMusic();

	sf::Sound gemSound;
	sf::SoundBuffer gemBuffer;
	sf::SoundBuffer hammerBuffer;
	sf::SoundBuffer boomBuffer;
	sf::SoundBuffer lightningBuffer;
	sf::SoundBuffer lavaBuffer;
	sf::Sound hammerSound;
	sf::Sound boomSound;
	sf::Sound lightningSound;
	sf::Sound lavaSound;
public:
	Game();
	~Game();

	// GETTERS

	// SETTERS

	// METHODS
	void prepareBoard(int level);
	int events(sf::Event e, sf::RenderWindow &window, Cursor *cursor);
	void drawing(sf::RenderWindow &window);
	bool gameEngine();

};

