#include "stdafx.h"
#include "Gem.h"

// CONTRUCTIONS
Gem::Gem(bool movable, sf::Vector2f position, int type)
	:Object(movable, position)
{
	this->type = type;
	this->position = position;
	this->value = type * 10;
	this->movable = movable;
	this->texture.loadFromFile("images/tiles.png");
	this->sprite.setPosition(position);
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::IntRect(40 * this->type, 0, 40, 40));
	this->match = 0;
	this->oldPosition = this->position;
	this->alpha = 255;
	this->sprite.setColor(sf::Color(255, 255, 255, this->alpha));


}
Gem::Gem()
{

}
Gem::~Gem()
{
}
// GETTERS
int Gem::getValue()
{
	return this->value;
}
int Gem::getMatch()
{
	return this->match;
}
int Gem::getAlpha()
{
	return this->alpha;
}
int Gem::getType()
{
	return this->type;
}
sf::Vector2f Gem::getOldPosition()
{
	return this->oldPosition;
}
sf::Vector2f Gem::getPosition()
{
	return this->position;
}

// SETTERS
void Gem::setTypeNotSprite(int type)
{
	this->type = type;
}
void Gem::setType(int type)
{
	this->type = type;
	this->sprite.setTextureRect(sf::IntRect(40 * this->type, 0, 40, 40));
}
void Gem::setAlpha(int alpha)
{
	this->alpha = alpha;
	this->sprite.setColor(sf::Color(255, 255, 255, alpha));
}
void Gem::setOldPosition(sf::Vector2f position)
{
	this->oldPosition = position;
}
void Gem::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->sprite.setPosition(position);
}

// METHODS
void Gem::drawGem(sf::RenderWindow &window)
{
	window.draw(this->sprite);
}
void Gem::updateTextrue(bool clicked)
{
	if (clicked == true)
	{
		this->texture.loadFromFile("images/tilesClicked.png");
		this->sprite.setTexture(this->texture);
	}
	else
	{
		this->texture.loadFromFile("images/tiles.png");
		this->sprite.setTexture(this->texture);
	}
}
void Gem::increaseMatch()
{
	this->match++;
}
void Gem::decreaseMatch()
{
	this->match = 0;
}
