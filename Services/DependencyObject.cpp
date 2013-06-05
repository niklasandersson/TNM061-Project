#include "DependencyObject.h"


DependencyObject::DependencyObject(std::string name) 
: Service(name)
{ }
		

bool 
DependencyObject::isUpdated() const
{ 
	for (unsigned int i = 0; i < _dependencies.size(); i++)
	{
		if (!_dependencies[i]->isUpdated())
			return false;
	}
	return true;
}
		

void 
DependencyObject::addDependency(Service* service) 
{
	for (int i = 0; i < _dependencies.size(); i++)
		if (_dependencies[i] == service)
			return;

	_dependencies.push_back(service);
}
	
	
void 
DependencyObject::removeDependency(Service* service) 
{	
	for (int i = 0; i < _dependencies.size(); i++)
	{
		if (_dependencies[i] == service)
		{
			_dependencies.erase(_dependencies.begin() + i);
			break;
		}
	}
}

