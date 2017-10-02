#pragma once
#include <SFML/Graphics.hpp>
#include "Windows.h"
class Menu:public Windows
{
	
	sf::Texture textureButtons;
	sf::Texture textureButtonsClicked;
	sf::Sprite buttonsMenu[4];

	sf::Vector2i mousePosition;

	void imagesUpdate(int i, bool clicked);
	void imagesUpdate(bool out);
public:
	Menu();
	~Menu();

	void drawMenu(sf::RenderWindow &window);
	int events(sf::Event e, sf::RenderWindow &window);
};

