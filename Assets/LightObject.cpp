#include "LightObject.h"

LightObject::LightObject(int maxNumberOfLights)
{
	_maxNumberOfLights = maxNumberOfLights;
	_numberOfLights = 0;
	initializeArrays();
}

LightObject::~LightObject()
{
	clearArrays();
}

bool
LightObject::addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity)
{
	if(_numberOfLights == _maxNumberOfLights)
		return false;
	else
	{
		_lightPositions[_numberOfLights] = direction;
		_lightIntensities[_numberOfLights] = intensity;
		_radii[_numberOfLights] = 0;
		_lightColors[_numberOfLights] = color;
		_lightTypes[_numberOfLights] = 0;
		_numberOfLights++;
	}

	return true;
}

bool
LightObject::addPointLight(glm::vec3 direction, glm::vec3 color, float intensity, float radius)
{
	if(_numberOfLights == _maxNumberOfLights)
		return false;
	else
	{
		_lightPositions[_numberOfLights] = direction;
		_lightIntensities[_numberOfLights] = intensity;
		_radii[_numberOfLights] = radius;
		_lightColors[_numberOfLights] = color;
		_lightTypes[_numberOfLights] = 1;
		_numberOfLights++;
	}

	return true;
}

void
LightObject::setMaxNumberOfLights(int maxNumberOfLights)
{	
	if(maxNumberOfLights != _maxNumberOfLights)
	{
		clearArrays();
		_maxNumberOfLights = maxNumberOfLights;
		initializeArrays();
	}
}

void
LightObject::clearArrays()
{

}

void 
LightObject::initializeArrays()
{
	_lightPositions = new glm::vec3[_maxNumberOfLights];
	_lightIntensities = new float[_maxNumberOfLights];
	_radii = new float[_maxNumberOfLights];
	_lightTypes = new int[_maxNumberOfLights];
	_lightColors = new glm::vec3[_maxNumberOfLights];
}

int
LightObject::getNumberOfLights()
{
	return _numberOfLights;
}

int
LightObject::getMaxNumberOfLights()
{
	return _maxNumberOfLights;
}


glm::vec3*
LightObject::getColors()
{
	return _lightColors;
}

glm::vec3*
LightObject::getPositions()
{
	return _lightPositions;
}

float*
LightObject::getIntensities()
{
	return _lightIntensities;
}

float*
LightObject::getRadii()
{
	return _radii;
}

int*
LightObject::getLightTypes()
{
	return _lightTypes;
}