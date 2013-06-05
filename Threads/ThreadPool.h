#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <iostream>
#include <vector>
#include <functional>
#include <deque>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "Worker.h"

class ThreadPool 
{
	public:
		ThreadPool(unsigned int nWorkers);

		void addJob(std::function<bool()> f);
		
		~ThreadPool();

		bool isEmpty() const;
	
	private:
		friend class Worker;

		std::vector<std::thread> _workers;
		std::deque< std::function<bool()> > _jobs;

		std::mutex _mutexQueue;
		std::condition_variable _conditionQueue;

		bool _isRunning;
		unsigned int _nWorkers;
};

#endif
