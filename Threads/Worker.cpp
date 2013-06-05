
#include "Worker.h"

Worker::Worker(ThreadPool* pool)
: _pool(pool)
{ }

// Worker thread
void
Worker::operator()()
{
	std::function<bool()> job;

	while (true)
	{
		{
			std::unique_lock<std::mutex> lock(_pool->_mutexQueue);
			
			while (_pool->_isRunning && _pool->_jobs.empty()) {
		//		std::cout << "Thread: " << std::this_thread::get_id() << " waiting.. " << std::endl;
				_pool->_conditionQueue.wait(lock);
			}

			if (!_pool->_isRunning)
				return;

			job = _pool->_jobs.front();
			_pool->_jobs.pop_front();
		}
			
		// Actual work
		if (!job()) 
		{
			std::unique_lock<std::mutex> lock(_pool->_mutexQueue);
			_pool->_jobs.push_back(job);
		//	std::cout << "Thread: " << std::this_thread::get_id() << " job put back." << std::endl;
		}
		
	}
}
