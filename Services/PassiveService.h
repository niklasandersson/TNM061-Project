#ifndef PASSIVESERVICE_H
#define PASSIVESERVICE_H

#include "Service.h"

class PassiveService : public Service
{

	public:
		PassiveService(std::string name);
		bool shouldUpdate();
	private:

};

#endif