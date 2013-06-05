#include "PngAnalyser.h"
#include <iostream>

PngAnalyser::PngAnalyser(std::string fileName)
: _fileName(fileName)
{
	lodepng::decode(_pixels, _X, _Y, _fileName);
	std::cout << "Size X: " << _X << std::endl;
	std::cout << "Size Y: " << _Y << std::endl;
	std::cout << "Total size: " << _pixels.size() <<std::endl;
	int j = 4;
	int x = 32;
	int y = 32;
	

}

std::vector<unsigned char>
PngAnalyser::getPixels()
{
	return _pixels;
}

unsigned int
PngAnalyser::getX()
{
	return _X;
}

unsigned int
PngAnalyser::getY()
{
	return _Y;
}

std::string
PngAnalyser::getFileName()
{
	return _fileName;
}

unsigned int
PngAnalyser::getColor(int x, int y)
{
	// 0 = white, 1 = Red, 2 = Green, 3 = Blue
	unsigned int	_color = 0;

	//To count the amount of steps in the vector _pixels
	//according to the sent coordinates if origo == (0,0)
	/*x = x*4;
	y = y*32;

	int r = x+y;
	int g = x+y + 1;
	int b = x+y + 2;*/

	int j = 4;
	int r = j*x+j*_X*y;
	int g = j*x+j*_X*y + 1;
	int b = j*x+j*_X*y + 2;

	//Get the value from the RGBA vector, alpha not used
	unsigned int	R = (int)_pixels[r], 
					G = (int)_pixels[g], 
					B = (int)_pixels[b];

	/*
	std::cout << "Red: " << R <<
		" Green: " << G << " Blue: " << B << std::endl;
	*/

	//if Red color
	if(	R >= 100	&& R <= 255	&&
		G >= 0		&& G <= 99	&&
		B >= 0		&& B <= 99){
		_color = 1;
	}
	//if Blue color
	else if(
		R >= 0		&& R <= 99	&&
		G >= 100	&& G <= 255	&&
		B >= 0		&& B <= 99){
		_color = 2;
	}
	//if Green color
	else if(
		R > 0		&& R <= 99	&&
		G >= 0		&& G <= 99	&&
		B >= 100	&& B <= 255){
		_color = 3;
	}
	//if white color
	else if(R == 0 && G == 0 && B == 0) _color = 0;

	//Return a Red, Green, Blue or White color
	return _color;
}