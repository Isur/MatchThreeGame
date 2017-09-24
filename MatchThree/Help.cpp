#include "stdafx.h"
#include "Help.h"


Help::Help()
{
	font.loadFromFile("font.ttf");
	text.setFont(font);
	text.setPosition(sf::Vector2f(0.0, 0.0));
	text.setString("CLICK SPACE TO START AGAIN. \nCLICK ESCAPE TO LEAVE. \nDESTROY EVERYTHING. \nICE BLOCKS BLOCK GEMS AND \nCANNOT BE MOVED. \nTO DESTROY THEM MOVE \nNEARBY GEMS.\n\n\n\n TO LEAVE PRESS ESC.");
}


Help::~Help()
{
}

void  Help::drawHelp(sf::RenderWindow &window)
{
	window.clear(sf::Color(40, 40, 40, 255));
	window.draw(text);
	window.display();
}
int Help::events(sf::Event e, sf::RenderWindow &window)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			return 0;
		}
	}


	return 3;
}