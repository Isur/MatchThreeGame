#include "stdafx.h"
#include "Help.h"


Help::Help()
	:Windows()
{
	backgroundTexture.loadFromFile("images/backgroundHelp.png");
	backgroundSprite.setTexture(backgroundTexture);
	buttonTexture.loadFromFile("images/backButtons.png");
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setTextureRect(sf::IntRect(0, 0, 275, 100));
	buttonSprite.setPosition(sf::Vector2f(250, 580));
}


Help::~Help()
{
}

void  Help::drawHelp(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
	window.draw(buttonSprite);
}
void Help::updateImage(bool clicked)
{
	if (clicked == true) buttonSprite.setTextureRect(sf::IntRect(0, 100, 275, 100));
	else buttonSprite.setTextureRect(sf::IntRect(0, 0, 275, 100));
}
int Help::events(sf::Event e, sf::RenderWindow &window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	if (mousePosition.x >= 250 && mousePosition.x <= 250 + 275)
	{
		if (mousePosition.y >= 580 && mousePosition.y <= 580 + 100)
		{
			updateImage(true);
		}
		else
		{
			updateImage(false);
		}
	}
	else
	{
		updateImage(false);
	}

	if (e.type == sf::Event::MouseButtonPressed)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		if (mousePosition.x >= 250 && mousePosition.x <= 250 + 275)
		{
			if (mousePosition.y >= 580 && mousePosition.y <= 580 + 100)
			{
				return 0;
			}
		}
	}
	return 3;
}