#include "stdafx.h"
#include "bgGem.h"


bgGem::bgGem(sf::Vector2f position, int type, int level)
	:Object(position, type, level)
{

	this->texture.loadFromFile("images/tilesBg.png");
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::IntRect(this->level * 40, 0, 40, 40));
	this->sprite.setPosition(this->position);
	this->alpha = 150;
	this->sprite.setColor(sf::Color(255, 255, 255, this->alpha));

}
bgGem::~bgGem()
{
}


// SETTERS
void bgGem::setLevel(int level)
{
	this->level = level;
	this->sprite.setTextureRect(sf::IntRect(this->level * 40, 0, 40, 40));
}
void bgGem::setType(int type)
{
	this->type = type;
	if (type == 1)
	{
		this->texture.loadFromFile("images/tileBg.png");
	}
}
//METHODS
void bgGem::drawBgGem(sf::RenderWindow &window)
{
	window.draw(this->sprite);
}

