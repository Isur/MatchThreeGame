#include "stdafx.h"
#include "FgGem.h"


FgGem::FgGem(int type, sf::Vector2f position, int level)
	:Object(position, type, level)
{
	if (this->type == 1) 
	{
		this->texture.loadFromFile("images/tilesFg.png");
	}
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::IntRect(this->level * 40, 0, 40, 40));
	this->sprite.setPosition(this->position);
	this->alpha = 255;
	this->sprite.setColor(sf::Color(255, 255, 255, this->alpha));
}

FgGem::~FgGem()
{
}

void FgGem::drawFgGem(sf::RenderWindow &window)
{
	this->sprite.setTextureRect(sf::IntRect(this->level * 40, 0, 40, 40));
	window.draw(this->sprite);
}