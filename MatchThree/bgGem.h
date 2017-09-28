#pragma once
#include<SFML\Graphics.hpp>
#include "Object.h"
class bgGem: Object
{
private:
	int level;
	int type;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	bgGem(bool movable, sf::Vector2f position, int type, int level);
	~bgGem();

	//GETTERS
	int getType();
	int getLevel();
	sf::Vector2f getPosition();
	//SETTERS
	void setLevel(int level);
	void setType(int type);
	void setPosition(sf::Vector2f position);
	void setAlpha(int alpha) { this->alpha = alpha; }
	//METHODS
	void drawBgGem(sf::RenderWindow &window);
};

