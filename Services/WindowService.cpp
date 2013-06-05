#include "WindowService.h"

WindowService::WindowService(Console* console)
: RenderingService("WindowService")
{
	_infoHandle = new InfoHandle();
	_console = console;
	initializeWindow();
}

WindowService::~WindowService()
{
	glfwTerminate();
}
		

void
WindowService::initializeWindow()
{
		_change = false;

		if (!glfwInit())
		{
			_isTerminationPending = true;
			_terminationMessage = "Could not initialize GLFW";
		}

		// --- OpenGL Configuration ---
		glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);                           // 4 times anti-aliasing
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);                   // OpenGL version 3
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);                   // OpenGL version 3.3
		glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Set OpenGl profile

		if (!glfwOpenWindow( _infoHandle->getWindowWidth(), _infoHandle->getWindowHeight(), 0,0,0,0, 32,0, GLFW_WINDOW))   // Open a window and create its OpenGL context
		//if ( !glfwOpenWindow( _infoHandle->getWindowWidth(), _infoHandle->getWindowHeight(), 0,0,0,0, 32,0, GLFW_FULLSCREEN ) )
		{	
			glfwTerminate();
			_isTerminationPending = true;
			_terminationMessage = "Could not open window";
		}

		glewExperimental = true;        // Needed for core profile
		if ( glewInit() != GLEW_OK )    // Initialize GLEW
    {
      _isTerminationPending = true;
			_terminationMessage = "Could not initialize GLEW";
		}

		_title = "Project";
		_newTitle = "Project";
		glfwSetWindowTitle(_title.c_str());

		_width = _infoHandle->getWindowWidth();
		_height = _infoHandle->getWindowHeight();
		_newWidth = _width;
		_newHeight = _height;

		setConsoleCommands();
}

void 
WindowService::setConsoleCommands()
{
	_console->quickAdd("setWindowTitle", this, &WindowService::setTitle);
	_console->quickAdd("setWindowSize", this, &WindowService::setWindowSize);
}

void 
WindowService::setTitle(std::string title)
{
	_newTitle = title;
	_change = true;
}

void 
WindowService::setWindowSize(unsigned int newWidth, unsigned int newHeight)
{
	_newWidth = newWidth;
	_newHeight = newHeight;
	_infoHandle->setWindowWidth(_newWidth);
	_infoHandle->setWindowHeight(_newHeight);
	_change = true;
}

void
WindowService::close()
{
		glfwTerminate();
}

void
WindowService::render()
{
	// Behöver ligga här, eftersom det är mainthreaden som kör render :)
	if (_change)
	{
		if (_title != _newTitle) 
		{
			glfwSetWindowTitle(_newTitle.c_str());
			_title = _newTitle;
		}

		if (_width != _newWidth || _height != _newHeight)
		{
			glfwSetWindowSize(_newWidth, _newHeight);
			_width = _newWidth;
			_height = _newHeight;
		}

		_change = false;
	}
}

void
WindowService::update()
{
	
}

InfoHandle*
WindowService::getInfoHandle()
{
	return _infoHandle;
}