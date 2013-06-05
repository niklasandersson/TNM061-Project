#ifndef AUDIO_H
#define AUDIO_H

#include<iostream>

#include <GL/glfw.h>

#include<windows.h>
#include<mmsystem.h>

#include "../Threads/ThreadPool.h"
#include "../Audio/Sound.h"
#include "../Utils/Console.h"

#define _NUMBER_OF_SOUNDS_ 20

typedef enum Sounds
{ 
		FOOTSTEP_1, 
		GUNSHOT_1,  
		GUNSHOT_2,
		CONSOLE,
		JUMP,
		SOUNDS_END
};

class Audio
{
	public:
		Audio(ThreadPool* thread_pool_real_time, Console* console);
		void play(unsigned int ID) const;

	private:
		ThreadPool* _pool;
		Sound** _sounds;
		Console* _console;

		void setConsoleCommands();
};

#endif