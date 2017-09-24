#pragma once
#include<SFML\Graphics.hpp>
#include "Object.h"
class Gem : protected Object
{
private:
	int type;
	int match;
	int value;
	bool underBlock;
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
	bool getChecked() { return this->checked; }
	bool getUnderBlock() { return this->underBlock; }
	// SETTERS
	void setPosition(sf::Vector2f position);
	void setOldPosition(sf::Vector2f position);
	void setAlpha(int alpha);
	void setType(int type);
	void setTypeNotSprite(int type);
	void setCheck(bool check) { this->checked = check; }
	void setUnderBlock(bool block) { this->underBlock = block; }
	// METHODS
	void drawGem(sf::RenderWindow &window);
	void updateTextrue(bool clicked);
	void increaseMatch();
	void decreaseMatch();



};