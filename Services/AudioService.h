#ifndef AUDIOSERVICE_H
#define AUDIOSERVICE_H

#include "PassiveService.h"
#include<iostream>
#include<windows.h>
#include<mmsystem.h>

class AudioService : public PassiveService
{
	public:
		AudioService();
		void playAudio(char ID);

	protected:

	private:

};

#endif