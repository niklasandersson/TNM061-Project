#ifndef INPUTSERVICE_H
#define INPUTSERVICE_H

#include "ActiveService.h"
#include "../Threads/ThreadPool.h"

#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Handles/InputHandle.h"
#include "../Handles/InfoHandle.h"
#include "../Utils/Audio.h"

#include "../Utils/Console.h"

#include <iostream>
#include <thread>

// Audio
#include <windows.h>
#include <mmsystem.h>
#include "../Audio/Sound.h"


class InputService : public ActiveService
{

	public:
		InputService(ThreadPool* _thread_pool_real_time, Console* console);
		void update();

		InputHandle* getInputHandle();
		void attachInfoHandle(InfoHandle* infoHandle);
		int getState();
	  
		static void GLFWCALL keyhandler33(int key, int action);
		

	private:
		InputHandle* _inputHandle;
		InfoHandle* _infoSlot;
		ThreadPool* _thread_pool_real_time;
		Audio* _audio;

		 static int running; 
		 static int keyrepeat; 
		 static int systemkeys; 

		Console* _console;	
		void setConsoleCommands();
		unsigned int _state;
		void setState(unsigned int state);
		void resetKeys();
		enum state {CONSOLE, INGAME};
		
		
};

#endif