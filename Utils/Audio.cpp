#include "Audio.h"

Audio::Audio(ThreadPool* pool, Console* console) 
{
	_pool = pool;
	_console = console;

	_sounds = new Sound*[_NUMBER_OF_SOUNDS_];

	_sounds[FOOTSTEP_1] = new Sound("../Audio/footstep.wav", 0.459); 
	_sounds[GUNSHOT_1]  = new Sound("../Audio/321628_SOUNDDOGS__gu2.wav", 0.16);
	_sounds[GUNSHOT_2]  = new Sound("../Audio/gunshot2.wav", 0.8);
	_sounds[CONSOLE]		= new Sound("../Audio/switch_to_console_edited.wav", 0.21);
	_sounds[JUMP]				= new Sound("../Audio/jump.wav", 1.1);

	setConsoleCommands();
}

void
Audio::setConsoleCommands()
{
	_console->addItem("playAudio", [=](std::string args) { 
		const unsigned int id = _console->getIntArg(args);
		if (id < SOUNDS_END)
			this->play(id); 
	});
}

void
Audio::play(unsigned int ID) const
{
	double thisTime = glfwGetTime();
	_pool->addJob(
		[=]
		{	
			if (_sounds[ID]->getLastTimePlusLength() < thisTime) 
			{
				std::string play = "play ";
				play.append(_sounds[ID]->getFileName());
				
				if (ID == GUNSHOT_1)
				 PlaySound(_sounds[ID]->getFileName(), NULL, SND_ASYNC | SND_FILENAME);

				else if (!mciSendString(play.c_str(), NULL, 0, NULL)) 
				{
						std::string stop = "stop ";
						stop.append(_sounds[ID]->getFileName());

						mciSendString(stop.c_str(), NULL, 0, NULL);
						mciSendString(play.c_str(), NULL, 0, NULL);
				}

				_sounds[ID]->setLastTime(thisTime);
			}
			return true;
		}
	);
	
}



