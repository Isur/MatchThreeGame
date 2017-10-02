#pragma once
#include<SFML\Graphics.hpp>
#include "Object.h"
class Gem : public Object
{
private:
	int match;
	int value;
	bool underBlock;


public:
	// CONSTRUCTORS
	Gem(sf::Vector2f position, int type);
	Gem();
	~Gem();
	// GETTERS
	int getMatch() {return this->match; }
	int getValue() { return this->value; }
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