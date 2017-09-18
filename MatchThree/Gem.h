#pragma once
#include<SFML\Graphics.hpp>
#include "Object.h"
class Gem : protected Object
{
private:
	int type;
	int match;
	int value;
	sf::Sprite sprite;
	sf::Texture texture;

public:
	// CONSTRUCTORS
	Gem(bool movable, sf::Vector2f position, int type);
	Gem();
	~Gem();
	// GETTERS
	int getType();
	int getMatch();
	int getAlpha();
	int getValue();
	sf::Vector2f getPosition();
	sf::Vector2f getOldPosition();

	// SETTERS
	void setPosition(sf::Vector2f position);
	void setOldPosition(sf::Vector2f position);
	void setAlpha(int alpha);
	void setType(int type);
	void setTypeNotSprite(int type);


	// METHODS
	void drawGem(sf::RenderWindow &window);
	void updateTextrue(bool clicked);
	void increaseMatch();
	void decreaseMatch();


};