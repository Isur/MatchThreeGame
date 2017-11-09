#include "stdafx.h"
#include "Menu.h"


Menu::Menu()
	:Windows()
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

	buttonHoverBuffer.loadFromFile("sounds/hover.wav");
	buttonHoverSound.setBuffer(buttonHoverBuffer);

	clickBuffer.loadFromFile("sounds/click.wav");
	clickSound.setBuffer(clickBuffer);

	music.openFromFile("sounds/menu_music.wav");
	music.setVolume(20);
	music.setLoop(true);
	isPlaying = false;

	isButtonHovered = false;
}
Menu::~Menu()
{
}
// METHODS
void Menu::drawMenu(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);
	for (int i = 0; i < 4; i++)
	{
		window.draw(buttonsMenu[i]);
	}

	// music :)
	if (!isPlaying) { music.play(); isPlaying = true; }
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
				if (!isButtonHovered) { buttonHoverSound.play(); isButtonHovered = true; }
			}
			else if (mousePosition.y >= 425 && mousePosition.y <= 525)
			{
				imagesUpdate(1, true);
				if (!isButtonHovered) { buttonHoverSound.play(); isButtonHovered = true; }
			}
			else if (mousePosition.y >= 550 && mousePosition.y <= 650)
			{
				imagesUpdate(2, true);
				if (!isButtonHovered) { buttonHoverSound.play(); isButtonHovered = true; }
			}
			else
			{
				imagesUpdate(true);
				isButtonHovered = false;
			}
		}
		else if (mousePosition.x >= 430 && mousePosition.x <= 430+100)
		{
			if (mousePosition.y >= 580 && mousePosition.y <= 580 + 100)
			{
				imagesUpdate(3, true);
				if (!isButtonHovered) { buttonHoverSound.play(); isButtonHovered = true; }
			}
			else
			{
				imagesUpdate(true);
				isButtonHovered = false;
			}
		}
		else 
		{
			imagesUpdate(true);
			isButtonHovered = false;
		}
	}
	if (e.type == sf::Event::MouseButtonPressed) 
	{
		clickSound.play();

		if (mousePosition.x >= 138 && mousePosition.x <= 138 + 275)
		{
			if (mousePosition.y >= 300 && mousePosition.y <= 400)
			{
				pauseMusic();
				return 4;
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

void Menu::pauseMusic()
{
	music.stop();
	isPlaying = false;
}