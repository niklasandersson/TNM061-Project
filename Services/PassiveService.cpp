#include "PassiveService.h"

PassiveService::PassiveService(std::string name)
: Service(name)
{

}

bool
PassiveService::shouldUpdate()
{
	return false;
}