#ifndef WORKER_H
#define WORKER_H

#include <vector>
#include <functional>
#include <deque>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "ThreadPool.h"

class ThreadPool;

class Worker
{
	public:
		Worker(ThreadPool* pool);
		void operator()();
	
	private:
		ThreadPool* _pool;
};

#endif
