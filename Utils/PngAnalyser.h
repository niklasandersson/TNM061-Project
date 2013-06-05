
#include <string>
#include <vector>

#include "lodepng.h"

class PngAnalyser
{
	public:
		PngAnalyser(std::string fileName);

		std::vector<unsigned char> getPixels();
		unsigned int getX();
		unsigned int getY();
		std::string getFileName();
		unsigned int getColor(int x, int y);

	private:
		const std::string _fileName;
		std::vector<unsigned char> _pixels;
		unsigned int _X;
		unsigned int _Y;
};