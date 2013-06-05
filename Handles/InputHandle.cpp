#include "InputHandle.h"

InputHandle::InputHandle()
{
	resetKeys();
}

void
InputHandle::resetKeys()
{
	for (int i = 0; i < NUMBER_OF_KEYS; ++i)
	{
		keys[i] = false;
	}
}

void
InputHandle::toggleKey(const unsigned int key)
{
	if (!keys[key])
		keys[key] = true;
	else
		keys[key] = false;
}

bool
InputHandle::isKeyDown(const unsigned int key)
{
	return keys[key];
}

void
InputHandle::setMousePosition(int mousePositionX, int mousePositionY)
{
	_mousePositionX = mousePositionX;
	_mousePositionY = mousePositionY;
}
		
void
InputHandle::getMousePosition(int& mousePositionX, int& mousePositionY)
{
	mousePositionX = _mousePositionX;
	mousePositionY = _mousePositionY;
}

int 
InputHandle::getState()
{
	return _state;
}

void 
InputHandle::setState(int state)
{
	_state = state;
}
