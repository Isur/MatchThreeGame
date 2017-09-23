#pragma once
#include <SFML/Graphics.hpp>
class Menu
{
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Vector2i mousePosition;
public:
	Menu();
	~Menu();

	void drawMenu(sf::RenderWindow &window);
	int events(sf::Event e, sf::RenderWindow &window);
};

