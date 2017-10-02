#include "stdafx.h"
#include "Cursor.h"


Cursor::Cursor()
{
	view.reset(sf::FloatRect(0, 0, 550, 700));
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
	window.setView(view);
	window.draw(sprite);
}

void Cursor::setTexture(int type)
{
	texture.loadFromFile("images/skills.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(type * 40, 0, 40, 40));
}

void Cursor::setDefaultTexture()
{
	this->texture.loadFromFile("images/cursor.png");
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
}
