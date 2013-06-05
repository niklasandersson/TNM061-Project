#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <string>

class TextObject
{
	public:
		TextObject(int x, int y);
		TextObject(std::string text, int x, int y);
		~TextObject();

		std::string getText();
		int getX();
		int getY();
		bool isVisible();
		void toggleVisible();

		void setVisible(bool isVisible);
		void setText(std::string text);
		void setPosition(int x, int y);
		void setX(int x);
		
	private:
		std::string _text;
		int _x;
		int _y;
		bool _isVisible;
};

#endif