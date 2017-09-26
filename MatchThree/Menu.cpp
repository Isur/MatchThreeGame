#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
{
	backgroundTexture.loadFromFile("images/menu.png");
	backgroundSprite.setTexture(backgroundTexture);

	textureButtons.loadFromFile("images/menuButtons.png");
	textureButtonsClicked.loadFromFile("images/menuButtonsClicked.png");

	for (int i = 0; i < 4; i++)
	{
		buttonsMenu[i].setTexture(textureButtons);
		buttonsMenu[i].setTextureRect(sf::IntRect(0, 100 * i, 275, 100));
	}
	buttonsMenu[3].setTextureRect(sf::IntRect(0, 100 * 3, 100, 100));
	
	buttonsMenu[0].setPosition(sf::Vector2f(138,300));
	buttonsMenu[1].setPosition(sf::Vector2f(138,425));
	buttonsMenu[2].setPosition(sf::Vector2f(138,550));
	buttonsMenu[3].setPosition(sf::Vector2f(430,580));
}
Menu::~Menu()
{
}
// METHODS
void Menu::drawMenu(sf::RenderWindow &window)
{
	window.clear(sf::Color(40,40,40,255));
	window.draw(backgroundSprite);
	for (int i = 0; i < 4; i++)
	{
		window.draw(buttonsMenu[i]);
	}
	window.display();
}

void Menu::imagesUpdate(int i, bool clicked)
{
	if(clicked == true)	buttonsMenu[i].setTexture(textureButtonsClicked);
	else buttonsMenu[i].setTexture(textureButtons);

	//buttonsMenu[i].setTextureRect(sf::IntRect(0, 100 * i, 275, 100));
}
void Menu::imagesUpdate(bool out)
{
	for (int i = 0; i < 4; i++)
	{
		buttonsMenu[i].setTexture(textureButtons);
	}
}

int Menu::events(sf::Event e, sf::RenderWindow &window)
{
	if (e.type == sf::Event::MouseMoved)
	{
		mousePosition = sf::Mouse::getPosition(window);
		if (mousePosition.x >= 138 && mousePosition.x <= 138 + 275)
		{
			if (mousePosition.y >= 300 && mousePosition.y <= 400)
			{
				imagesUpdate(0, true);
			}
			else if (mousePosition.y >= 425 && mousePosition.y <= 525)
			{
				imagesUpdate(1, true);
			}
			else if (mousePosition.y >= 550 && mousePosition.y <= 650)
			{
				imagesUpdate(2, true);
			}
			else
			{
				imagesUpdate(true);
			}
		}
		else if (mousePosition.x >= 430 && mousePosition.x <= 430+100)
		{
			if (mousePosition.y >= 580 && mousePosition.y <= 580 + 100)
			{
				imagesUpdate(3, true);
			}
			else
			{
				imagesUpdate(true);
			}
		}
		else 
		{
			imagesUpdate(true);
		}
	}
	if (e.type == sf::Event::MouseButtonPressed) 
	{
		if (mousePosition.x >= 138 && mousePosition.x <= 138 + 275)
		{
			if (mousePosition.y >= 300 && mousePosition.y <= 400)
			{
				return 1;
			}
			else if (mousePosition.y >= 425 && mousePosition.y <= 525)
			{
				return 2;
			}
			else if (mousePosition.y >= 550 && mousePosition.y <= 650)
			{
				window.close();
			}
		}
		else if (mousePosition.x >= 430 && mousePosition.x <= 430 + 100)
		{
			if (mousePosition.y >= 580 && mousePosition.y <= 580 + 100)
			{
				return 3;
			}
		}
	}
	return 0;
}