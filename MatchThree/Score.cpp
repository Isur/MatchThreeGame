#include "stdafx.h"
#include "Score.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
Score::Score()
{
	std::string scoreString;
	font.loadFromFile("font.ttf");
	for (int i = 0; i < 10; i++)
	{
		text[i].setFont(font);
		text[i].setPosition(sf::Vector2f(200.0, 60.0*(i+1)));
		text[i].setFillColor(sf::Color::White);
	}

	std::ifstream scoreFile;
	scoreFile.open("score/score.egg");
	for (int i = 0; i < 10; i++)
	{
		std::getline(scoreFile, scoreString);
		text[i].setString(std::to_string(i+1) + ". " + scoreString.substr(3, scoreString.size()));
	}
}


Score::~Score()
{
}

void Score::drawScore(sf::RenderWindow & window)
{
	window.clear(sf::Color(40, 40, 40, 255));
	//window.draw(backgroundSprite);
	for (int i = 0; i < 10; i++) window.draw(text[i]);
	window.display();
}

void Score::checkIfTop(int score)
{
	int scoreArray[10];
	std::ifstream scoreFile;
	scoreFile.open("score/score.egg");
	std::string scoreString = "";

	for (int i = 0; i < 10; i++)
	{
		std::getline(scoreFile, scoreString);
		int size = scoreString.size();
		std::istringstream iss( scoreString.substr(3, size));
		iss >> scoreArray[i];
	}

	if (score > scoreArray[9])
	{
		scoreArray[9] = score;
		printf("%i > %i", score, scoreArray[9]);
	}
	int max, temp;
	for (int i = 0; i < 10; i++)
	{
		max = i;
		for (int j = i+1; j < 10; j++)
		{
			if (scoreArray[i] < scoreArray[j])
			{
				max = j;
			}
		}
		temp = scoreArray[max];
		scoreArray[max] = scoreArray[i];
		scoreArray[i] = temp;
	}

	scoreFile.close();
	std::ofstream scoreFileOut;
	scoreFileOut.open("score/score.egg", std::ios::out);
	for (int i = 0; i < 10; i++)
	{
		scoreString = std::to_string(i) + ". " + std::to_string(scoreArray[i]);
		scoreFileOut << scoreString << std::endl;
	}
	scoreFileOut.close();
}
