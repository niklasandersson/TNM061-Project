
#include "ThreadPool.h"

ThreadPool::ThreadPool(unsigned int nWorkers)
: _isRunning(true), _nWorkers(nWorkers)
{
	for (unsigned int i = 0; i < _nWorkers; i++)
		_workers.push_back(std::thread(Worker(this)));
}


ThreadPool::~ThreadPool()
{
	std::cout << std::endl << "Pool die, joining all threads." << std::endl;
	_isRunning = false;
	_conditionQueue.notify_all();
	
	for (unsigned int i = 0; i < _nWorkers; i++)
		_workers[i].join();
}

// Add job
void
ThreadPool::addJob(std::function<bool()> f)
{
	std::unique_lock<std::mutex> lock(_mutexQueue);
	_jobs.push_back(f);
	_conditionQueue.notify_one();
}

bool 
ThreadPool::isEmpty() const
{
	return _jobs.empty();
}

