#include "Kernel.h"

Kernel::Kernel(ThreadPool* thread_pool, Console* console)
{
	_thread_pool = thread_pool;
	_console = console;

	setConsoleCommands();
}

void 
Kernel::setConsoleCommands()
{
	_console->quickAdd("quit", this, &Kernel::stop);
}

Kernel::~Kernel()
{

}

void
Kernel::start()
{
		_isRunning = true;
}

void
Kernel::stop()
{
    _isRunning = false;
}

bool
Kernel::isRunning() const
{
    return _isRunning;
}

void
Kernel::update()
{

	#if _THREADS_
	
		ActiveService* ran;
		for (unsigned int i = 0; i < _activeServices.size(); i++) 
		{
			ran = _activeServices[i];
			_thread_pool->addJob( 
				[ran]
				{ 
					if (ran->getDependency() && !ran->getDependency()->isUpdated()) 
						return false;  // Do some other wosrk in the meantime
					else
					{
						ran->update();
						ran->setUpdated(true);
						return true;  // Job done
					}
				}
			);
		}
	
	#else 

		for (unsigned int i = 0; i < _activeServices.size(); i++)
			_activeServices[i]->update();

	#endif 
	
	// Look for termination requests
/*
	for (unsigned int i = 0; i < _activeServices.size(); i++)
	{
		if (_activeServices[i]->isRequestingTermination(_errorMessage))
		{
			std::cout << _errorMessage;
			stop();
		}
	}
*/

	#if _THREADS_

		// Wait for all updates
		unsigned int d = 0;
		unsigned int size = _activeServices.size();
		while (!d)
		{
			for (d = 0; d < size; d++) 
			{
				if (!_activeServices[d]->isUpdated())  // Wait for all updates
				{
					d = 0;
					break;
				}
			}
		}

	#endif 

} 


void
Kernel::render()
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (unsigned int i = 0; i < _renderingServices.size(); i++)
		_renderingServices[i]->render();

	glfwSwapBuffers();	
}


void
Kernel::sync()
{
	for (unsigned int i = 0; i < _activeServices.size(); i++)
		_activeServices[i]->setUpdated(false);

	for (unsigned int i = 0; i < _renderingServices.size(); i++)
		_renderingServices[i]->setUpdated(false);
	
	while (!_thread_pool->isEmpty())  // Wait for all threads
		std::cout << "SYNC" << std::endl; 

}


void
Kernel::addActiveService(ActiveService* service)
{
    _activeServices.push_back(service);
}


void
Kernel::addRenderingService(RenderingService* service)
{
    _renderingServices.push_back(service);
    _activeServices.push_back((ActiveService*)service);
}


void
Kernel::addPassiveService(PassiveService* service)
{
    _passiveServices.push_back(service);
}

