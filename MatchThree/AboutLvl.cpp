#include "stdafx.h"
#include "AboutLvl.h"


AboutLvl::AboutLvl()
{
}

AboutLvl::AboutLvl(std::string lvlType, int level)
	:Windows()
{
	backgroundTexture.loadFromFile("images/aboutLvl.png");
	backgroundSprite.setTexture(backgroundTexture);
	buttonTexture.loadFromFile("images/play.png");
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setTextureRect(sf::IntRect(0, 0, 300, 125));
	buttonSprite.setPosition(sf::Vector2f(125, 300));

	clickBuffer.loadFromFile("sounds/click.wav");
	clickSound.setBuffer(clickBuffer);

	myFont.loadFromFile("font.ttf");
	
	
	if (lvlType == "points") goalText.setString("You have to earn\n " + std::to_string(level*2500) + " points");
	else if (lvlType == "ice") goalText.setString("You have to destroy\n all ice on map!");
	else if (lvlType == "background") goalText.setString("You have to destroy\n everything under\ngems");
	else if (lvlType == "all") goalText.setString("You have to destroy\neverything on map!");
	
	lvlText.setFont(myFont);
	lvlText.setPosition(sf::Vector2f(110.0, 100.0));

	lvlText.setString("This is " + std::to_string(level)+" level");

	goalText.setFont(myFont);
	goalText.setPosition(sf::Vector2f(110.0, 140.0));

}


AboutLvl::~AboutLvl()
{
}

void AboutLvl::drawAboutLvl(sf::RenderWindow & window)
{
	window.draw(backgroundSprite);
	window.draw(goalText);
	window.draw(lvlText);
	window.draw(buttonSprite);
}

int AboutLvl::events(sf::Event e, sf::RenderWindow & window)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	if (mousePosition.y >= 300 && mousePosition.y <= 425)
	{
		if (mousePosition.x >= 125 && mousePosition.x <= 425)
		{
			updateImage(true);
			if (e.type == sf::Event::MouseButtonPressed)
			{
				clickSound.play();
				delete this;
				return 1;
			}
		}
		else updateImage(false);
	}
	else updateImage(false);
	return 0;
}


void AboutLvl::updateImage(bool im)
{
	if (im == true)
		buttonSprite.setTextureRect(sf::IntRect(0, 125, 300, 125));
	else
		buttonSprite.setTextureRect(sf::IntRect(0, 0, 300, 125));
}