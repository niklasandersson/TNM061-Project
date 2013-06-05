#ifndef DEPENDENCYOBJECT_H
#define DEPENDENCYOBJECT_H

#include <vector>
#include <string>

#include "Service.h"

class DependencyObject : public Service
{
	public:
		DependencyObject(std::string name);
		bool isUpdated() const;
		void addDependency(Service* service);
		void removeDependency(Service* service);

	private:
		std::vector<Service*> _dependencies;
};

#endif