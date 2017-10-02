#pragma once
#include<SFML\Graphics.hpp>
class Object
{
protected:
	int alpha;
	int type;
	int level;
	bool checked;
	sf::Vector2f position;
	sf::Vector2f oldPosition;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Object(int type);
	Object(sf::Vector2f position, int type);
	Object(sf::Vector2f position, int type, int level);
	Object();
	~Object();
		
	// GETTERS
	int getType() { return this->type; }
	int getAlpha() { return this->alpha; }
	sf::Vector2f getPosition() { return this->position; }
	sf::Vector2f getOldPosition() { return this->oldPosition; }
	bool getChecked() { return this->checked; }

	// SETTERS
	void setType(int type) { this->type = type; }
	void setAlpha(int alpha) { this->alpha = alpha; }
	void setPosition(sf::Vector2f position) { this->position = position; }


};

