#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Windows.h"
class Menu:public Windows
{
	
	sf::Texture textureButtons;
	sf::Texture textureButtonsClicked;
	sf::Sprite buttonsMenu[4];

	sf::Vector2i mousePosition;

	sf::SoundBuffer clickBuffer;
	sf::Sound clickSound;
	sf::SoundBuffer buttonHoverBuffer;
	sf::Sound buttonHoverSound;
	sf::Music music;
	bool isButtonHovered;
	bool isPlaying;
	void pauseMusic();

	void imagesUpdate(int i, bool clicked);
	void imagesUpdate(bool out);
public:
	Menu();
	~Menu();

	void drawMenu(sf::RenderWindow &window);
	int events(sf::Event e, sf::RenderWindow &window);
};

