#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Windows.h"
class AboutLvl:public Windows
{

	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;

	sf::SoundBuffer clickBuffer;
	sf::Sound clickSound;
	sf::SoundBuffer hoverBuffer;
	sf::Sound hoverSound;
	bool isHovered;

	sf::Font myFont;
	sf::Text goalText;
	sf::Text lvlText;

	void updateImage(bool im);
public:
	AboutLvl();
	AboutLvl(std::string lvlType, int level);
	~AboutLvl();
	void drawAboutLvl(sf::RenderWindow& window);
	int events(sf::Event e, sf::RenderWindow &window);
};

