#pragma once
#include <SFML\Graphics.hpp>
#include "Object.h"
#include "settings.h"

class Skills:public Object
{
private: 
	int quantity;
	sf::Font font;
	sf::Text text;
public:
	Skills(int type);
	~Skills();
	void drawSkills(sf::RenderWindow &window);

	int getQuantity() { return this->quantity; }
	void setQuantity(int quantity) { this->quantity = quantity; }
	sf::Texture getTexture() { return this->texture; }
};

