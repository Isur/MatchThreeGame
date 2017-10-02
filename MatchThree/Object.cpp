#include "stdafx.h"
#include "Object.h"

Object::Object(int type)
{
	this->type = type;
}

Object::Object(sf::Vector2f position, int type)
{
	this->position = position;
	this->type = type;
}

Object::Object(sf::Vector2f position, int type, int level)
{
	this->position = position;
	this->type = type;
	this->level = level;
}


Object::Object()
{

}
Object::~Object()
{

}
