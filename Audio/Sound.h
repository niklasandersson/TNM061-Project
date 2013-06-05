#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <string>

class Sound
{
	public:
		Sound(char* fileName, double length) 
		{
			_fileName = fileName;
			_length = length;
			_lastTime = 0;
		}
	
		char* getFileName() const;

		double getLastTimePlusLength() const;
		void setLastTime(double lastTime);

		double getLenth() const;
		double getLastTime() const;

	private:
		char* _fileName;

		double _length;
		double _lastTime;
};

#endif