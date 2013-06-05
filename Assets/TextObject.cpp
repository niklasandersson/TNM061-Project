#include "TextObject.h"

TextObject::TextObject(int x, int y)
{
	_text = "";
	_x = x;
	_y = y;
	_isVisible = true;
}

TextObject::TextObject(std::string text, int x, int y)
{
	_text = text;
	_x = x;
	_y = y;
	_isVisible = true;
}

void
TextObject::setVisible(bool isVisible)
{
	_isVisible = isVisible;
}

void
TextObject::toggleVisible()
{
	_isVisible = _isVisible ? false : true;
}

void
TextObject::setText(std::string text)
{
	_text = text;
}

void
TextObject::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void 
TextObject::setX(int x)
{
		_x = x;
}

std::string
TextObject::getText()
{
	return _text;
}

int
TextObject::getX()
{
	return _x;
}

int
TextObject::getY()
{
	return _y;
}

bool
TextObject::isVisible()
{
	return _isVisible;
}
