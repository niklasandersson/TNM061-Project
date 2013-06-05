#ifndef ACTIVESERVICE_H
#define ACTIVESERVICE_H

#include "Service.h"

class ActiveService : public Service
{
	public:
		ActiveService(std::string name);
		virtual void update() = 0;
		bool shouldUpdate();
		bool isUpdating();

	protected:
		void startUpdating();
		void stopUpdating();

	private:
		int _updatePriority;
		bool _isUpdating;
};

#endif