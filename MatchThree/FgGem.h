#pragma once
#include <SFML\Graphics.hpp>
#include "Object.h"
class FgGem :public Object
{

public:
	FgGem(int type, sf::Vector2f position, int level);
	~FgGem();

	// GETTERS
	int getLevel() { return this->level; }
	// SETTERS
	void setLevel(int level) { this->level = level; }
	// METHODS
	void drawFgGem(sf::RenderWindow &window);
};

