#pragma once
#include <SFML\Graphics.hpp>
class Help
{
private:
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Texture buttonTexture;
	sf::Sprite buttonSprite;

	void Help::updateImage(bool clicked);
public:
	Help();
	~Help();

	int events(sf::Event e, sf::RenderWindow &window);
	void drawHelp(sf::RenderWindow &window);
};

