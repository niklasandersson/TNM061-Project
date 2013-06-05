#include "AudioService.h"

AudioService::AudioService()
: PassiveService("AudioService")
{

}

void
AudioService::playAudio(char ID)
{
	switch (ID)
	{
		//One footstep
		case '0':
			PlaySound(TEXT("../Audio/footstep.wav"), NULL, SND_ASYNC | SND_FILENAME);
			break;
		//Many footsteps
		case '1': 
			PlaySound(TEXT("../Audio/footsteps.wav"), NULL, SND_ASYNC | SND_FILENAME);
			break;
		//Buzz Mars is talking about space and stuff...
		case '2': 
			PlaySound(TEXT("../Audio/buzzmars.wav"), NULL, SND_ASYNC | SND_FILENAME);
			break;
		default: 
			break;
	}
}