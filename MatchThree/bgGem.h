#pragma once
#include<SFML\Graphics.hpp>
#include "Object.h"
class bgGem : public Object
{
private:

public:
	bgGem(sf::Vector2f position, int type, int level);
	~bgGem();

	//GETTERS

	int getLevel() { return this->level; }

	//SETTERS
	void setLevel(int level);
	void setType(int type);
	//METHODS
	void drawBgGem(sf::RenderWindow &window);
};

