#include "InfoHandle.h"

InfoHandle::InfoHandle()
{
	_windowWidth = 1024;
	_windowHeight = 768;
}

int
InfoHandle::getWindowWidth()
{
	return _windowWidth;
}

int
InfoHandle::getWindowHeight()
{
	return _windowHeight;
}

void
InfoHandle::setWindowWidth(int windowWidth)
{
	_windowWidth = windowWidth;
}

void
InfoHandle::setWindowHeight(int windowHeight)
{
	_windowHeight = windowHeight;
}

void
InfoHandle::setIsJumping(bool isJumping)
{
	_isJumping = isJumping;
}

bool
InfoHandle::getIsJumping()
{
	return _isJumping;
}