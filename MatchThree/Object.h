#pragma once
#include<SFML\Graphics.hpp>
class Object
{
protected:
	bool movable;
	int alpha;
	bool checked;
	sf::Vector2f position;
	sf::Vector2f oldPosition;

public:
	Object(bool movable, sf::Vector2f position);
	Object();
	~Object();
		

};

