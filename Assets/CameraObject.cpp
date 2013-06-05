#include "CameraObject.h"


CameraObject::CameraObject(float fov, float aspectRatio, float clippingRangeNear, float clippingRangeFar, 
						glm::vec3 position, glm::vec3 lookAt, glm::vec3 orientation)
{
	_position = position;
	_lookingAt = lookAt;
	_orientation = orientation;

	_fov = fov;
	_aspectRatio = aspectRatio;
	_clippingRangeNear = clippingRangeNear;
	_clippingRangeFar = clippingRangeFar;

	_projection = glm::perspective(_fov, _aspectRatio, _clippingRangeNear, _clippingRangeFar);
	_view = glm::lookAt(_position, _lookingAt, _orientation);

	_lookingSpeed = 0.004f;
	_movmentSpeed = 20.0001f;
}

void
CameraObject::setProjectionMatrix(glm::mat4 projection)
{
	_projection = projection;
}

void
CameraObject::setViewMatrix(glm::mat4 view)
{
	_view = view;
}

void
CameraObject::addToPosition(glm::vec3 position)
{
	_position += position;
}

void
CameraObject::subtractFromPosition(glm::vec3 position)
{
	_position -= position;
}

void
CameraObject::setPosition(glm::vec3 position)
{
	_position = position;
	_view = glm::lookAt(_position, _lookingAt, _orientation);
}

void
CameraObject::setYPosition(float yPos)
{
	_position.y = yPos;
	_view = glm::lookAt(_position, _lookingAt, _orientation);
}

void
CameraObject::setLookingAt(glm::vec3 lookingAt)
{
	_lookingAt = lookingAt;
	_view = glm::lookAt(_position, _lookingAt, _orientation);
}

void
CameraObject::setOrientation(glm::vec3 orientation)
{
	_orientation = orientation;
	_view = glm::lookAt(_position, _lookingAt, _orientation);
}

void
CameraObject::setFieldOfView(float fov)
{
	_fov = fov;
	_projection = glm::perspective(_fov, _aspectRatio, _clippingRangeNear, _clippingRangeFar);
}

void
CameraObject::setAspectRation(float aspectRatio)
{
	_aspectRatio = aspectRatio;
	_projection = glm::perspective(_fov, _aspectRatio, _clippingRangeNear, _clippingRangeFar);
}

void
CameraObject::setClippingRangeNear(float clippingRangeNear)
{
	_clippingRangeNear = clippingRangeNear;
	_projection = glm::perspective(_fov, _aspectRatio, _clippingRangeNear, _clippingRangeFar);
}

void
CameraObject::setClippingRangeFar(float clippingRangeFar)
{
	_clippingRangeFar = clippingRangeFar;
	_projection = glm::perspective(_fov, _aspectRatio, _clippingRangeNear, _clippingRangeFar);
}

void
CameraObject::setMovmentSpeed(float movmentSpeed)
{
	_movmentSpeed = movmentSpeed;
}

void
CameraObject::setLookingSpeed(float lookingSpeed)
{
	_lookingSpeed = lookingSpeed;
}

glm::vec3&
CameraObject::getPosition()
{
	return _position;
}

glm::vec3&
CameraObject::getLookingAt()
{
	return _lookingAt;
}

glm::vec3&
CameraObject::getOrientation()
{
	return _orientation;
}

float&
CameraObject::getFieldOfView()
{
	return _fov;
}

float&
CameraObject::getAspectRatio()
{
	return _aspectRatio;
}

float&
CameraObject::getClippingRangeNear()
{
	return _clippingRangeNear;
}

float&
CameraObject::getClippingRangeFar()
{
	return _clippingRangeFar;
}

glm::mat4&
CameraObject::getProjectionMatrix()
{
	return _projection;
}

glm::mat4&
CameraObject::getViewMatrix()
{
	return _view;
}

glm::mat4*
CameraObject::getViewMatrixPointer()
{
	return &_view;
}

float&
CameraObject::getMovmentSpeed()
{
	return _movmentSpeed;
}

float&
CameraObject::getLookingSpeed()
{
	return _lookingSpeed;
}

