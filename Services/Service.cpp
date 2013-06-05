#include "Service.h"


Service::Service(std::string name)
: _name(name)
{
	_isUpdated = false;
	_dependOn = NULL;
	_isTerminationPending = false;
	_terminationMessage = "Genereic termination message";
}


std::string 
Service::getName() const
{
	return _name;
} 


bool 
Service::isRequestingTermination(std::string& terminationMessage)
{
	std::string appendingMessage = "Termination requested by ";
	std::string devider = ": ";
	terminationMessage = appendingMessage + _name + devider + _terminationMessage;
	return _isTerminationPending;
}

// For thread pool

bool 
Service::isUpdated() const 
{ 
	return Service::_isUpdated;
}

void
Service::setUpdated(bool isUpdated)
{
	_isUpdated = isUpdated;
}


Service* 
Service::getDependency() const
{
	return _dependOn;
}


void 
Service::setDependency(Service* dependOn)
{
	_dependOn = dependOn;
}
		

void 
Service::addDependency(Service* service) 
{
	std::cout << this->getName() << " has no DependencyObject, can't addDependency." << std::endl;
}


void 
Service::removeDependency(Service* service)
{
	std::cout << this->getName() << " has no DependencyObject, can't removeDependency." << std::endl;
}