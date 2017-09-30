#pragma once
#include <SFML\Graphics.hpp>
class Cursor
{
private:
	sf::View view;
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite sprite;
	
public:
	Cursor();
	~Cursor();

	void move(sf::Vector2i position);
	void drawCursor(sf::RenderWindow &window);
};

