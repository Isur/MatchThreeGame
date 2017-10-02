#include "stdafx.h"
#include "Skills.h"


Skills::Skills(int type)
	:Object(type)
{
	quantity = 1;
	font.loadFromFile("font.ttf");
	text.setFont(font);
	
	position = sf::Vector2f(OFFSET_X + 2*type*TILESIZE, OFFSET_Y + SIZE_Y*TILESIZE + 10);

	texture.loadFromFile("images/skills.png");
	sprite.setPosition(position);
	position.y += 40;
	text.setPosition(position);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(type * 40, 0, 40, 40));
}


Skills::~Skills()
{
}

void Skills::drawSkills(sf::RenderWindow &window)
{

	text.setString(std::to_string(quantity));
	window.draw(sprite);
	window.draw(text);
}