#include "ActiveService.h"

ActiveService::ActiveService(std::string name)
: Service(name)
{

}

bool
ActiveService::shouldUpdate()
{
	return true;
}

void
ActiveService::startUpdating()
{
	_isUpdating = true;
}

void
ActiveService::stopUpdating()
{
	_isUpdating = false;
}

bool
ActiveService::isUpdating()
{
	return _isUpdating;
}