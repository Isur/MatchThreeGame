#pragma once
#include <SFML\Graphics.hpp>
#include "Windows.h"
class Help:public Windows
{
private:

	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;

	void Help::updateImage(bool clicked);
public:
	Help();
	~Help();

	int events(sf::Event e, sf::RenderWindow &window);
	void drawHelp(sf::RenderWindow &window);
};

