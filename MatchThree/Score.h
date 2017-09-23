#pragma once
#include <SFML\Graphics.hpp>
class Score
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Font font;
	sf::Text text[10];
	int score[10];

public:
	Score();
	~Score();

	// METHODS
	void drawScore(sf::RenderWindow &window);
	int events(sf::Event e, sf::RenderWindow &window);
	void checkIfTop(int score);
};

