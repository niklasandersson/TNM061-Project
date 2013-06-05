#ifndef WINDOWSERVICE_h
#define WINDOWSERVICE_h

#include "RenderingService.h"

#include <iostream>
#include <sstream>

#include <GL/glew.h>
#include <GL/glfw.h>

#include "../Handles/InfoHandle.h"

#include "../Utils/Console.h"

class WindowService : public RenderingService
{
	public:
		WindowService(Console* console);
		~WindowService();
		
		void render();
		void update();
		void close();

		void setTitle(std::string title);
	  void setWindowSize(unsigned int width, unsigned int height);

		InfoHandle* getInfoHandle();

	private:
		bool isWorking;

		void initializeWindow();

		InfoHandle* _infoHandle;
		
		Console* _console;
		std::string _title;
		std::string _newTitle;

		unsigned int _width;
		unsigned int _height;
		unsigned int _newWidth;
		unsigned int _newHeight;
		bool _change;
		
		void setConsoleCommands();

};

#endif
