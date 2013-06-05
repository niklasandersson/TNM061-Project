#include <iostream>
#include <thread>

#include "Threads/ThreadPool.h"
#include "Kernel.h"

#include "Services/DependencyObject.h"

#include "Services/WindowService.h"
#include "Services/SceneService.h"
#include "Services/InputService.h"
#include "Services/TextService.h"

#include "Utils/Console.h"


int
main(void)
{
	
	const unsigned int NUMBER_OF_THREADS = std::thread::hardware_concurrency();

	#if _THREADS_

	std::cout << "ThreadPool initialized with " 
					  << NUMBER_OF_THREADS - 1 
						<< " workers." << std::endl;

		ThreadPool* thread_pool = new ThreadPool(NUMBER_OF_THREADS - 2);
		ThreadPool* thread_pool_real_time = new ThreadPool(1);

	#else

		ThreadPool* thread_pool = new ThreadPool(1);
		ThreadPool* thread_pool_real_time = new ThreadPool(1);

	#endif

	Console* console = new Console();
	Kernel* kernel = new Kernel(thread_pool, console);

	WindowService* window_service = new WindowService(console);

	InputService* input_service = new InputService(thread_pool_real_time, console);
	input_service->attachInfoHandle(window_service->getInfoHandle());

	TextService* text_service = new TextService("../../Textures/VerdanaBold.tga");

	SceneService* scene_service = new SceneService("../../Images/testBlock.png", console);
	scene_service->attachInputHandle(input_service->getInputHandle());
	scene_service->attachInfoHandle(window_service->getInfoHandle());
	scene_service->attachTextHandle(text_service->getTextHandle());
		
	// Testar
	console->attachTextHandle(text_service->getTextHandle());
	

	DependencyObject* scene_dependency = new DependencyObject("scene_dependency");
	scene_dependency->addDependency(window_service);
	scene_dependency->addDependency(input_service);
	scene_service->setDependency(scene_dependency);

	kernel->addRenderingService(window_service);
	kernel->addActiveService(input_service);
	kernel->addRenderingService(scene_service);
	kernel->addRenderingService(text_service);

	kernel->start();

	while (kernel->isRunning())
	{
		kernel->update();
		kernel->render();
		kernel->sync();
  }

	delete kernel;
	delete thread_pool;
	delete window_service;
	delete input_service;
	delete scene_service;
	delete scene_dependency;
	delete thread_pool_real_time;

	char goodBye;
	std::cin >> goodBye;

	return 0;
}
