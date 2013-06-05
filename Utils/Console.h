#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <functional>
#include <typeinfo>


#include "../Handles/TextHandle.h"
#include "../Assets//TextObject.h"


struct CommandItem
{
	CommandItem(std::string name, std::function<void(std::string)> function)
	{
		name_			= name;
		function_ = function;
	}
	std::function<void(std::string)> function_;
	std::string name_;
};


class Console
{
	public:

		Console()
		{
			setCommand("");
			setPrevious(0);
			_position = 0;

			initializeConsole();	
			_isDisplayingInfo = false;
		}
		
		void initializeConsole()
		{
			
			
			// --- Instructions ---
			// -------------------------------------------------------------------		
			//
			// How to use the console, type:
			//
			// "ITEM NAME" "ARG1" "ARG2" "ARG3" "ARGn"
			//
			// -------------------------------------------------------------------		
			//
			// Add items with quickAdd if possible.
			//
			// quickAdd("ITEM NAME", POINTER TO OBJECT, REFERENCE TO FUNCTION);
			//
			// Exist quickAdd templates for void functions with these arguments:
			// void
			// (void) const
			// int
			// int int 
			// int int int
			// string
			// char
			// bool
			// char*
			// const char*
			// float
			// float float
			// float float float
			// unsigned int
			// unsigned int, unsigned int
			// unsigned int, unsigned int, unsigned int
			//
			// --------------------------------------------------------------------
			//
			// Use addItem for more complicated functions:
			//
			// addItem("ITEM NAME", [VARIABLES](std::string args) { WHAT TO DO });
			//
			// --------------------------------------------------------------------


			// --- Console Items ---
			// quit
			// setWindowSize INT INT
			// setWindowTitle STRING
			// playAudio INT
			// his 
			// clearHis
			// cmd
			// close
			// showFPS BOOL
			// showGrid BOOL

			quickAdd("his", this, &Console::displayCommandHistory);
			quickAdd("clearHis", this, &Console::clearCommandHistory);
			quickAdd("cmd", this, &Console::displayCommands);

		}

		void addItem(const std::string& name, std::function<void(std::string)> function)
		{
			bool isAlreadyAdded = false;
			
			for_each (_commandItems.begin(), _commandItems.end(), 
				[&isAlreadyAdded, &name](CommandItem& item)
				{
					if (item.name_ == name) 
					{
						isAlreadyAdded = true;
						std::cout << "Command " << name << " is already in the list..." << std::endl;
						return;
					}
				}
			);

			if (!isAlreadyAdded)
			{
				_commandItems.push_back(CommandItem(name, function));
				std::cout << "Added command: " << name << std::endl;
			}
		}
		
		void passChar(const char& c)
		{
			_isDisplayingInfo = false;
			_command.insert(_command.begin() + _position, c);
			passPositionRight();
			updateText();
			//std::cout << "Passed char: " << c << std::endl;
		}	

		void passBackSpace()
		{
			_isDisplayingInfo = false;
			if (_position > 0)
			{
				passPositionLeft();
				_command.erase(_command.begin() + _position);
				updateText();
			}
		}	

		void passDel()
		{
			if (_position >= 0)
			{
				_command.erase(_command.begin() + _position);
				updateText();
			}
		}	

		void passPositionRight()
		{
			if (_position < _command.size())
			{
				_position ++;
				updatePositionText();
			}
		}

		void passPositionLeft()
		{
			if (_position > 0)
			{
				_position --;	
				updatePositionText();
			}			
		}

		void passPreviousUp()
		{
			if (_previous < _commandHistory.size() - 1)
				_previous ++;
	
			if (_commandHistory.size() > 0)
			{
				_command = _commandHistory[_previous];
				_position = _commandHistory[_previous].size();
				updateText();
			}
		}

		void passPreviousDown()
		{
			if (_previous > 0)
				_previous --;		

			if (_commandHistory.size() > 0)
			{
				_command = _commandHistory[_previous];
				_position = _commandHistory[_previous].size();
				updateText();
				
			}
		}

		void setPosition(unsigned int position)
		{
			if (position <= _command.size())
			{
				_position = position;	
				updatePositionText();
			}
		}

		void setPrevious(unsigned int previous)
		{
			if (previous <= _commandHistory.size())
				_previous = previous;
		}
		
		void displayCommand() const
		{
			std::cout << _command << std::endl;
		}

		void setCommand(std::string command)
		{
			_command = command;
		}
		
		void clearCommand()
		{
			setCommand("");
			setPrevious(0);
			setPosition(0);
		}

		void updatePositionText()
		{
			_positionObject->setX(22 + _position*17);
		}
	
		void updateText(std::string s)
		{
			if (!_isDisplayingInfo) 
			{
				if (_commandHistory.size() > 2)
					_textObject->setText(">" + s + "\n" + _commandHistory[0] + "\n" + _commandHistory[1] + "\n" + _commandHistory[2] + "\n");

				else if (_commandHistory.size() > 1)
					_textObject->setText(">" + s + "\n" + _commandHistory[0] + "\n" + _commandHistory[1] + "\n");

				else if (_commandHistory.size() > 0)
					_textObject->setText(">" + s + "\n" + _commandHistory[0] + "\n");

				else 
					_textObject->setText(">" + s + "\n");

				updatePositionText();
				_positionObject->setText("|");
			}
		}

		void updateText()
		{
			updateText(_command);
		}

		unsigned int getPosition() const
		{
			return _position;
		}
		
		std::deque<std::string> getCommandHistory() const
		{
			return _commandHistory;
		}

		void clearCommandHistory()
		{
			_commandHistory.clear();
		}
		
		void displayCommandHistory()
		{
			std::string temp = "";
			for_each (_commandHistory.rbegin(), _commandHistory.rend(),
				[&](std::string line)
				{
					temp += "\"" + line + "\"\n";
				}
			);
			temp += "History:";
			std::cout << temp << std::endl;

			_isDisplayingInfo = true;
			_textObject->setText(temp);

		}

		void displayCommands()
		{
			std::string temp = "";
			for_each (_commandItems.begin(), _commandItems.end(),
				[&](CommandItem item)
				{
					temp += "\"" + item.name_ + "\"\n";
				}
			);
			temp += "Commands:";
			std::cout << temp << std::endl;
			
			_isDisplayingInfo = true;
			_textObject->setText(temp);
		}

		void executeCommand()
		{
			std::cout << "Execute: " << _command << std::endl;
			
			bool isExecuted = false;
			std::istringstream is(_command);
			std::string name, args;

			is >> name >> std::ws;
			getline(is, args);
			
			for_each (_commandItems.begin(), _commandItems.end(), 
				[&name, &args, &isExecuted, this](CommandItem& item)
				{
					if (item.name_ == name) 
					{
						std::cout << "Executing: " << name << "(" << args << ")" << std::endl;

						try 
						{
							item.function_(args);
						}
						catch (...)
						{
							std::cout << "Failed to execute: " << name << "(" << args << ")" << std::endl;
							std::string s =  "Failed to execute: " + name + "(" + args + ")";
							updateText(s);
						}

						isExecuted = true;
						return;
					}
				}
			);

			if (!isExecuted) 
			{
				std::cout << "No matching command: " << name << std::endl;
				std::string s = "No matching command: " + name;
				_commandHistory.push_front(s);
			} 
			else 
			{
				_commandHistory.push_front(_command);
			}
			
			clearCommand();
			updateText();
		}



		// Just for now (LEAGACY)
		int getIntArg(std::string args)
		{
			std::istringstream is(args);
			int tal;
			is >> std::ws >> tal;
			return tal;
		}

		float getFloatArg(std::string args)
		{
			std::istringstream is(args);
			float tal;
			is >> std::ws >> tal;
			return tal;
		}

		void testFunctionMultiple(std::string name, float f1, float f2, float f3)
		{
				std::cout << "Testing, MULTIPLE: " << name << " " << f1 << " " << f2 << " " << f3 << std::endl;
		}
		
		void testFunctionInt3Args(int r, int g, int b)
		{
			std::cout << "Testing, color: " << r << " " << g << " " << b << std::endl;

		}

		void testFunctionString(std::string args)
		{
			std::cout << "Testing, args: " << args << std::endl;
		}

		void testFunctionInt(int tal)
		{
			std::cout << "Testing, tal: " << tal << std::endl;
		}
	
		void testFunctionFloat(float tal)
		{
			std::cout << "Testing, tal: " << tal << std::endl;
		}
		
		void testFunctionBool(bool b)
		{
			std::cout << "Testing, bool: " << b << std::endl;
		}
		// End of Legacy		


		void attachTextHandle(TextHandle* textHandle)
		{
			_textHandle = textHandle;
			_textObject = new TextObject(10, 10);
			_positionObject = new TextObject(10, 10);
			_textHandle->addText(_positionObject);
			_textHandle->addText(_textObject);
		}

		void setConsoleVisibility(bool isVisible)
		{
			_textObject->setVisible(isVisible);
		}		

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)())
		{
			addItem(name, [t, f](std::string args) { (t->*f)(); });
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)() const)
		{
			addItem(name, [t, f](std::string args) { (t->*f)(); });
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(std::string))
		{
			addItem(name, [t, f](std::string args) { (t->*f)(args); });
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(const char*))
		{
			addItem(name, [t, f](std::string args) { 
				const char* cstr = args.c_str();
				(t->*f)(cstr); 
			});
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(char*))
		{
			addItem(name, [t, f](std::string args) { 
				char* cstr = args.c_str();
				(t->*f)(cstr); 
			});
		}
	
		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(int))
		{
			addItem(name, [t, f](std::string args) { 
				std::istringstream is(args);
				int tal;
				is >> tal;
				(t->*f)(tal); 
			});
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(int, int))
		{
			addItem(name, [t, f](std::string args) { 
				std::istringstream is(args);
				int tal[2];
				is >> tal[0] >> tal[1];
				(t->*f)(tal[0], tal[1]); 
			});
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(int, int, int))
		{
			addItem(name, [t, f](std::string args) { 
				std::istringstream is(args);
				int tal[3];
				is >> tal[0] >> tal[1] >> tal[2];
				(t->*f)(tal[0], tal[1], tal[2]); 
			});
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(unsigned int))
		{
			addItem(name, [t, f](std::string args) { 
				std::istringstream is(args);
				unsigned int tal;
				is >> tal;
				(t->*f)(tal); 
			});
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(unsigned int, unsigned int))
		{
			addItem(name, [t, f](std::string args) { 
				std::istringstream is(args);
				unsigned int tal[2];
				is >> tal[0] >> tal[1];
				(t->*f)(tal[0], tal[1]); 
			});
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(unsigned int, unsigned int, unsigned int))
		{
			addItem(name, [t, f](std::string args) { 
				std::istringstream is(args);
				unsigned int tal[3];
				is >> tal[0] >> tal[1] >> tal[2];
				(t->*f)(tal[0], tal[1], tal[2]); 
			});
		}
		
		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(float))
		{
			addItem(name, [t, f](std::string args) { 
				std::istringstream is(args);
				float tal;
				is >> tal;
				(t->*f)(tal); 
			});
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(float, float))
		{
			addItem(name, [t, f](std::string args) { 
				std::istringstream is(args);
				float tal[2];
				is >> tal[0] >> tal[1];
				(t->*f)(tal[0], tal[1]); 
			});
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(float, float, float))
		{
			addItem(name, [t, f](std::string args) { 
				std::istringstream is(args);
				float tal[3];
				is >> tal[0] >> tal[1] >> tal[2];
				(t->*f)(tal[0], tal[1], tal[2]); 
			});
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(char))
		{
			addItem(name, [t, f](std::string args) { 
				std::istringstream is(args);
				char c;
				is >> c;
				(t->*f)(c); 
			});
		}

		template<typename T>
		inline void quickAdd(const std::string& name, T* t, void (T::*f)(bool))
		{
			addItem(name, [t, f](std::string args) { 
				std::transform(args.begin(), args.end(), args.begin(), tolower);
				if (args == "true")
				{
					(t->*f)(true); 
					return;
				} 
				else if (args == "false")
				{
					(t->*f)(false); 
					return;
				} 
				std::istringstream is(args);
				bool b;
				is >> b;
				(t->*f)(b); 
			});
		}

		TextObject* getPostionObject()
		{
			return _positionObject;
		}

		bool isDisplayingInfo()
		{
			return _isDisplayingInfo;
		}

	private:
		std::deque<std::string> _commandHistory;
		std::list<CommandItem> _commandItems;
		
		std::string _command;		
		unsigned int _position;
		bool _isDisplayingInfo;
		unsigned int _previous;
		TextHandle* _textHandle;
		TextObject* _textObject;
		TextObject* _positionObject;

};

#endif