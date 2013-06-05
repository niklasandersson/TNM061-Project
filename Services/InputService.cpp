#include "InputService.h"

struct KeyhandlerContainer
{
	KeyhandlerContainer(Console* console, Audio* audio) 
	{
		_console = console;
		_audio = audio;
	}
	private:
		static Console* _console;
		static Audio* _audio;
		friend void keyhandler(int key, int action);
		friend void charhandler(int key, int action);
};
Console* KeyhandlerContainer::_console = NULL;
Audio* KeyhandlerContainer::_audio = NULL;

void GLFWCALL
charhandler(int key, int action)
{ 
	if (action != GLFW_PRESS)
		return;
  
	// std::cout << "CHARhandler: " << key << std::endl;

	if (key >= 0 && key < 256 && key != 167)
		KeyhandlerContainer::_console->passChar((char)key);
}

void GLFWCALL
keyhandler(int key, int action)
{ 
	if (action != GLFW_PRESS)
		return;
  
	// std::cout << "KEYhandler: " << key << std::endl;

	switch (key)
  {
		case GLFW_KEY_LEFT:
			KeyhandlerContainer::_console->passPositionLeft();
    break;
	
		case GLFW_KEY_RIGHT:
			KeyhandlerContainer::_console->passPositionRight();
    break;

		case GLFW_KEY_UP:
			KeyhandlerContainer::_console->passPreviousUp();
    break;
	
		case GLFW_KEY_DOWN:
			KeyhandlerContainer::_console->passPreviousDown();
    break;

		case GLFW_KEY_BACKSPACE:
			KeyhandlerContainer::_console->passBackSpace();
    break;
	
		case GLFW_KEY_DEL:
			KeyhandlerContainer::_console->passDel();
    break;

		case GLFW_KEY_ENTER:
			KeyhandlerContainer::_console->executeCommand();
    break;
		
		case GLFW_KEY_KP_ENTER:
			KeyhandlerContainer::_console->executeCommand();
		break;
   }
}

InputService::InputService(ThreadPool* thread_pool_real_time, Console* console)
: ActiveService("InputService")
{
	_thread_pool_real_time = thread_pool_real_time;
	_audio = new Audio(thread_pool_real_time, console);
	const KeyhandlerContainer consolecontainer(console, _audio);

	_inputHandle = new InputHandle();
	glfwEnable(GLFW_STICKY_KEYS);
	glfwEnable(GLFW_KEY_REPEAT);
	glfwEnable(GLFW_SYSTEM_KEYS);

	_console = console;
	setConsoleCommands();

	_state = INGAME;
	_inputHandle->setState(_state);
}

// Ska tas bort sen tillsammans med keyhandler33
	int InputService::running = 1; 
	int InputService::keyrepeat = 0; 
	int InputService::systemkeys = 1; 

void
InputService::update()
{

	if(_infoSlot == NULL)
	{
		_isTerminationPending = true;
		_terminationMessage = "Missing InfoHandle";
	}
	else
	{
		int mousePositionX, mousePositionY;
		glfwGetMousePos(&mousePositionX, &mousePositionY);
		_inputHandle->setMousePosition(mousePositionX, mousePositionY);
		

		_inputHandle->resetKeys();
		
		if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) {
			//std::cout << "Pressed ESC" << std::endl;
			_inputHandle->toggleKey(InputHandle::KEY_ESC);
		}

	  if(glfwGetKey(167) == GLFW_PRESS && glfwGetKey(167) == GLFW_RELEASE)
		{
				//std::cout << "PRESSED 167" << std::endl;
				_audio->play(3);	
				
				if (_state == INGAME)
				{
					setState(CONSOLE);
					_inputHandle->setState(_state);
				}
				else if (_state == CONSOLE)
				{
					setState(INGAME);
					_inputHandle->setState(_state);
				}
			
				_console->clearCommand();
				_console->updateText();
				resetKeys();
		}
		
		// Legacy :) Still needed though
		if(_state == INGAME)
		{	
			if(glfwGetKey('A') == GLFW_PRESS) {
				//std::cout << "Pressed A" << std::endl;
				if(!_infoSlot->getIsJumping())
					_audio->play(0);

				_inputHandle->toggleKey(InputHandle::KEY_A);
			}
			
			if(glfwGetKey('S') == GLFW_PRESS) {
				//std::cout << "Pressed S" << std::endl;
			if(!_infoSlot->getIsJumping())
				_audio->play(0);

				_inputHandle->toggleKey(InputHandle::KEY_S);
			}

			if(glfwGetKey('D') == GLFW_PRESS) {
				//std::cout << "Pressed D" << std::endl;
			if(!_infoSlot->getIsJumping())
				_audio->play(0);

				_inputHandle->toggleKey(InputHandle::KEY_D);
			}

			if(glfwGetKey('W') == GLFW_PRESS) {
				//std::cout << "Pressed W" << std::endl;	
			if(!_infoSlot->getIsJumping())
				_audio->play(0);

				_inputHandle->toggleKey(InputHandle::KEY_W);
			}

			if(glfwGetKey(GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				_audio->play(4);
				_inputHandle->toggleKey(InputHandle::KEY_SPACE);
			}

			if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
				//std::cout << "Mouse 1" << std::endl;		
				_audio->play(1);
			}

			if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
				//std::cout << "Mouse 1" << std::endl;		
				_audio->play(2);
			}
		}

		/*if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS || !glfwGetWindowParam(GLFW_OPENED))
		{
				_isTerminationPending = true;
				_terminationMessage = "Termination by user input";
		}*/
	}

}

void
InputService::setConsoleCommands()
{
	_console->addItem("close", [this](std::string) { 
		this->_audio->play(3);
		this->setState(INGAME); 
		_inputHandle->setState(_state);
		this->resetKeys();
	});
}

void 
InputService::setState(unsigned int state)
{
	switch (state)
	{
		case CONSOLE :
			std::cout << "Enter state: CONSOLE" << std::endl;
			_state = CONSOLE;
			_console->setConsoleVisibility(true);
			glfwSetCharCallback(charhandler);	
			glfwSetKeyCallback(keyhandler);
		break;
	
		case INGAME :
			std::cout << "Enter state: INGAME" << std::endl;
			_state = INGAME;
			_console->setConsoleVisibility(false);
			glfwSetCharCallback(NULL);
			glfwSetKeyCallback(NULL);
		break;
	}
}

void
InputService::resetKeys()
{
	for (unsigned int i = 0; i < 256; i++)
	{
		glfwGetKey(i);
	}
}

int 
InputService::getState()
{
	return _state;
}

InputHandle*
InputService::getInputHandle()
{
	return _inputHandle;
}

void
InputService::attachInfoHandle(InfoHandle* infoHandle)
{
	_infoSlot = infoHandle;
}


// Test ska tas bort sen
void GLFWCALL 
InputService::keyhandler33(int key, int action) 
{ 
	if (action != GLFW_PRESS)
	{
		//std::cout << "No key pressed, returns" << std::endl;
		return;
  }
	
	switch (key)
  {
		case GLFW_KEY_ESC:
				printf("Escape\n");
       break;
		case GLFW_KEY_F1:
		case GLFW_KEY_F2:
		case GLFW_KEY_F3:
		case GLFW_KEY_F4:
   case GLFW_KEY_F5:
   case GLFW_KEY_F6:
   case GLFW_KEY_F7:
   case GLFW_KEY_F8:
   case GLFW_KEY_F9:
   case GLFW_KEY_F10:
   case GLFW_KEY_F11:
   case GLFW_KEY_F12:
   case GLFW_KEY_F13:
   case GLFW_KEY_F14:
   case GLFW_KEY_F15:
   case GLFW_KEY_F16:
   case GLFW_KEY_F17:
   case GLFW_KEY_F18:
   case GLFW_KEY_F19:
   case GLFW_KEY_F20:
   case GLFW_KEY_F21:
   case GLFW_KEY_F22:
   case GLFW_KEY_F23:
   case GLFW_KEY_F24:
   case GLFW_KEY_F25:
       printf( "F%d\n", 1 + key - GLFW_KEY_F1 );
       break;
   case GLFW_KEY_UP:
       printf( "UP\n" );
       break;
   case GLFW_KEY_DOWN:
       printf( "DOWN\n" );
       break;
   case GLFW_KEY_LEFT:
       printf( "LEFT\n" );
       break;
   case GLFW_KEY_RIGHT:
       printf( "RIGHT\n" );
       break;
   case GLFW_KEY_LSHIFT:
       printf( "LSHIFT\n" );
       break;
   case GLFW_KEY_RSHIFT:
       printf( "RSHIFT\n" );
       break;
   case GLFW_KEY_LCTRL:
       printf( "LCTRL\n" );
       break;
   case GLFW_KEY_RCTRL:
       printf( "RCTRL\n" );
       break;
   case GLFW_KEY_LALT:
       printf( "LALT\n" );
       break;
   case GLFW_KEY_RALT:
       printf( "RALT\n" );
       break;
   case GLFW_KEY_TAB:
       printf( "TAB\n" );
       break;
   case GLFW_KEY_ENTER:
       printf( "ENTER\n" );
       break;
   case GLFW_KEY_BACKSPACE:
       printf( "BACKSPACE\n" );
       break;
   case GLFW_KEY_INSERT:
       printf( "INSERT\n" );
       break;
   case GLFW_KEY_DEL:
       printf( "DEL\n" );
       break;
   case GLFW_KEY_PAGEUP:
       printf( "PAGEUP\n" );
       break;
   case GLFW_KEY_PAGEDOWN:
       printf( "PAGEDOWN\n" );
       break;
   case GLFW_KEY_HOME:
       printf( "HOME\n" );
       break;
   case GLFW_KEY_END:
       printf( "END\n" );
       break;
   case GLFW_KEY_KP_0:
			
       printf( "KEYPAD 0\n" );
       break;
   case GLFW_KEY_KP_1:
       printf( "KEYPAD 1\n" );
       break;
   case GLFW_KEY_KP_2:
       printf( "KEYPAD 2\n" );
       break;
   case GLFW_KEY_KP_3:
       printf( "KEYPAD 3\n" );
       break;
   case GLFW_KEY_KP_4:
       printf( "KEYPAD 4\n" );
       break;
   case GLFW_KEY_KP_5:
       printf( "KEYPAD 5\n" );
       break;
   case GLFW_KEY_KP_6:
       printf( "KEYPAD 6\n" );
       break;
   case GLFW_KEY_KP_7:
       printf( "KEYPAD 7\n" );
       break;
   case GLFW_KEY_KP_8:
       printf( "KEYPAD 8\n" );
       break;
   case GLFW_KEY_KP_9:
       printf( "KEYPAD 9\n" );
       break;
   case GLFW_KEY_KP_DIVIDE:
       printf( "KEYPAD DIVIDE\n" );
       break;
   case GLFW_KEY_KP_MULTIPLY:
       printf( "KEYPAD MULTIPLY\n" );
       break;
   case GLFW_KEY_KP_SUBTRACT:
       printf( "KEYPAD SUBTRACT\n" );
       break;
   case GLFW_KEY_KP_ADD:
       printf( "KEYPAD ADD\n" );
       break;
   case GLFW_KEY_KP_DECIMAL:
       printf( "KEYPAD DECIMAL\n" );
       break;
   case GLFW_KEY_KP_EQUAL:
       printf( "KEYPAD =\n" );
       break;
   case GLFW_KEY_KP_ENTER:
       printf( "KEYPAD ENTER\n" );
       break;
   case GLFW_KEY_SPACE:
       printf( "SPACE\n" );
       break;
   case 'R':
       keyrepeat = (keyrepeat+1) & 1;
       if( keyrepeat )
       {
				glfwEnable( GLFW_KEY_REPEAT );
				std::cout << "Enable GLFW_KEY_REPEAT" << std::endl;
       }
       else
       {
           glfwDisable( GLFW_KEY_REPEAT );
						std::cout << "Disable GLFW_KEY_REPEAT" << std::endl;
       }
       printf( "R => Key repeat: %s\n", keyrepeat ? "ON" : "OFF" );
       break;
   case 'S':
       systemkeys = (systemkeys+1) & 1;
       if( systemkeys )
       {
           glfwEnable( GLFW_SYSTEM_KEYS );
       }
       else
       {
           glfwDisable( GLFW_SYSTEM_KEYS );
       }
       printf( "S => System keys: %s\n", systemkeys ? "ON" : "OFF" );
       break;
   default:
       if( key > 0 && key < 256 )
       {
           printf( "%c\n", (char) key );
       }
       else
       {
           printf( "???\n" );
       }
       break;
   }

	fflush( stdout );
}





/*******************************************************************
GLFW_KEY_SPACE						Space
GLFW_KEY_ESC							Escape
GLFW_KEY_Fn								Function key n (n can be in the range 1..25)
GLFW_KEY_UP								Cursor up
GLFW_KEY_DOWN							Cursor down
GLFW_KEY_LEFT							Cursor left
GLFW_KEY_RIGHT						Cursor right
GLFW_KEY_LSHIFT						Left shift key
GLFW_KEY_RSHIFT						Right shift key
GLFW_KEY_LCTRL					 Left control key
GLFW_KEY_RCTRL						Right control key
GLFW_KEY_LALT							Left alternate function key
GLFW_KEY_RALT							Right alternate function key
GLFW_KEY_LSUPER						Left super key, WinKey, or command key
GLFW_KEY_RSUPER						Right super key, WinKey, or command key
GLFW_KEY_TAB							Tabulator
GLFW_KEY_ENTER						Enter
GLFW_KEY_BACKSPACE				Backspace
GLFW_KEY_INSERT						Insert
GLFW_KEY_DEL							Delete
GLFW_KEY_PAGEUP						Page up
GLFW_KEY_PAGEDOWN					Page down
GLFW_KEY_HOME							Home
GLFW_KEY_END							End
GLFW_KEY_KP_n							Keypad numeric key n (n can be in the range 0..9)
GLFW_KEY_KP_DIVIDE				Keypad divide ()
GLFW_KEY_KP_MULTIPLY			Keypad multiply ()
GLFW_KEY_KP_SUBTRACT			Keypad subtract (􀀀)
GLFW_KEY_KP_ADD						Keypad add (+)
GLFW_KEY_KP_DECIMAL				Keypad decimal (. or ,)
GLFW_KEY_KP_EQUAL					Keypad equal (=)
GLFW_KEY_KP_ENTER					Keypad enter
GLFW_KEY_KP_NUM_LOCK			Keypad num lock
GLFW_KEY_CAPS_LOCK				Caps lock
GLFW_KEY_SCROLL_LOCK			Scroll lock
GLFW_KEY_PAUSE						Pause key
GLFW_KEY_MENU							Menu key
********************************************************************/