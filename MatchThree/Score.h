#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
class Score
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;
	sf::Font font;
	sf::Text text[10];
	int score[10];
	void updateImage(bool clicked);

	sf::SoundBuffer clickBuffer;
	sf::Sound clickSound;
	sf::SoundBuffer hoverBuffer;
	sf::Sound hoverSound;
	bool isButtonHovered;
public:
	Score();
	~Score();

	// METHODS
	void drawScore(sf::RenderWindow &window);
	int events(sf::Event e, sf::RenderWindow &window);
	void checkIfTop(int score);
};

