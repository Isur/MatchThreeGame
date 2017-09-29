#include "stdafx.h"
#include "Cursor.h"


Cursor::Cursor()
{
	this->texture.loadFromFile("images/cursor.png");
	this->sprite.setTexture(texture);
	this->sprite.setPosition(position);
}


Cursor::~Cursor()
{
}

void Cursor::move(sf::Vector2i position)
{
	this->position.x = (float) position.x;
	this->position.y = (float) position.y;
	this->sprite.setPosition(this->position);
}

void Cursor::drawCursor(sf::RenderWindow &window)
{
	window.draw(sprite);
}