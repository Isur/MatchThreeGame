#include "stdafx.h"
#include "Skills.h"


Skills::Skills(int type)
	:Object(type)
{
	quantity = 0;
	font.loadFromFile("font.ttf");
	text.setFont(font);
	
	position = sf::Vector2f((float)OFFSET_X + 2.0f*type*TILESIZE,(float) OFFSET_Y + SIZE_Y*TILESIZE + 10.0f);

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