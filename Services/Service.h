#ifndef SERVICE_H
#define SERVICE_H

#include <iostream>
#include <string>

class Service
{
	public:
		Service(std::string name);
		std::string getName() const;
		virtual bool isRequestingTermination(std::string& errorMessage);
		
		virtual bool isUpdated() const;
		void setUpdated(bool isUpdated);
		Service* getDependency() const;
		void setDependency(Service* dependOn);
		virtual void addDependency(Service* service);
		virtual void removeDependency(Service* service);


	protected:
		bool _isUpdated;
		bool _isTerminationPending;
		std::string _terminationMessage;
		
	private:
		const std::string _name;
		Service* _dependOn;
};

#endif
