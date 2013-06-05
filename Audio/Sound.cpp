#include "Sound.h"


char* 
Sound::getFileName() const
{
	return _fileName;
}


double 
Sound::getLastTimePlusLength() const 
{
	return _lastTime + _length;
}


void 
Sound::setLastTime(double lastTime)  
{
	_lastTime = lastTime;
}


double 
Sound::getLenth() const
{
	return _length;
}


double 
Sound::getLastTime() const
{
	return _lastTime;
}

