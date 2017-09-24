#pragma once
#include <SFML\Graphics.hpp>
class Help
{
private:
	sf::Font font;
	sf::Text text;
public:
	Help();
	~Help();

	int events(sf::Event e, sf::RenderWindow &window);
	void drawHelp(sf::RenderWindow &window);
};

