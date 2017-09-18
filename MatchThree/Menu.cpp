#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
{

	backgroundTexture.loadFromFile("images/menu.png");
	backgroundSprite.setTexture(backgroundTexture);


}


Menu::~Menu()
{
}

void Menu::drawText(sf::RenderWindow &window)
{
	window.clear(sf::Color(40,40,40,255));
	window.draw(backgroundSprite);
	window.display();
}
bool Menu::events(sf::Event e, sf::RenderWindow &window)
{
	if (e.type == sf::Event::MouseMoved)
	{
		mousePosition = sf::Mouse::getPosition(window);
		if (mousePosition.x >= 138 && mousePosition.x <= 138 + 275)
		{
			if (mousePosition.y >= 300 && mousePosition.y <= 400)
			{
				backgroundTexture.loadFromFile("images/menuPlay.png");
				backgroundSprite.setTexture(backgroundTexture);
			}
			else if (mousePosition.y >= 425 && mousePosition.y <= 525)
			{
				backgroundTexture.loadFromFile("images/menuScores.png");
				backgroundSprite.setTexture(backgroundTexture);
			}
			else if (mousePosition.y >= 550 && mousePosition.y <= 650)
			{
				backgroundTexture.loadFromFile("images/menuExit.png");
				backgroundSprite.setTexture(backgroundTexture);
			}
			else
			{
				backgroundTexture.loadFromFile("images/menu.png");
				backgroundSprite.setTexture(backgroundTexture);
			}
		}
		else 
		{
			backgroundTexture.loadFromFile("images/menu.png");
			backgroundSprite.setTexture(backgroundTexture);
		}
	}
	if (e.type == sf::Event::MouseButtonPressed) 
	{
		if (mousePosition.x >= 138 && mousePosition.x <= 138 + 275)
		{
			if (mousePosition.y >= 300 && mousePosition.y <= 400)
			{
				return true;
			}
			else if (mousePosition.y >= 425 && mousePosition.y <= 525)
			{
				
			}
			else if (mousePosition.y >= 550 && mousePosition.y <= 650)
			{
				window.close();
			}
		}
	}
}