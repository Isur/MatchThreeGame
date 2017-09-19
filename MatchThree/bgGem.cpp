#include "stdafx.h"
#include "bgGem.h"


bgGem::bgGem(bool movable, sf::Vector2f position, int type)
	:Object(movable, position)
{
	this->position = position;
	this->movable = movable;
	this->type = type;
	this->level = 2;
	if (this->type == 1)
	{
		this->texture.loadFromFile("images/tilesBg.png");
	}
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::IntRect(this->level * 40, 0, 40, 40));
	this->sprite.setPosition(this->position);
	this->alpha = 150;
	this->sprite.setColor(sf::Color(255, 255, 255, this->alpha));

}
bgGem::~bgGem()
{
}

// GETTERS
int bgGem::getLevel()
{
	return this->level;
}
int bgGem::getType()
{
	return this->type;
}
sf::Vector2f bgGem::getPosition()
{
	return this->position;
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
void bgGem::setPosition(sf::Vector2f position)
{
	this->position = position;
}
//METHODS
void bgGem::drawBgGem(sf::RenderWindow &window)
{
	window.draw(this->sprite);
}

