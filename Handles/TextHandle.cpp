#include "TextHandle.h"

TextHandle::TextHandle()
{
	_text  = "";
	_texts.reserve(10);

}

TextHandle::~TextHandle()
{

}

std::string
TextHandle::getText(int i)
{
	return _texts[i]->getText();
}

int
TextHandle::getX(int i)
{
	return _texts[i]->getX();
}

int
TextHandle::getY(int i)
{
	return _texts[i]->getY();
}

bool
TextHandle::isVisible(int i)
{
	return _texts[i]->isVisible();
}

void
TextHandle::addText(TextObject* text)
{
	_texts.push_back(text);
}

int
TextHandle::getNumberOfTextObjects()
{
	return _texts.size();
}