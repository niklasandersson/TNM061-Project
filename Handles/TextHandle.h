#ifndef TEXTHANDLE_H
#define TEXTHANDLE_H

#include <string>
#include <vector>

#include "../Assets/TextObject.h"

class TextHandle
{
	public:
		TextHandle();
		~TextHandle();

		std::string getText(int i);
		int getX(int i);
		int getY(int i);
		bool isVisible(int i);

		void addText(TextObject* text);

		int getNumberOfTextObjects();

	private:
		std::string _text;
		std::vector<TextObject*> _texts;

};
#endif