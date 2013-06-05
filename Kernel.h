#ifndef KERNEL_H
#define KERNEL_H

#include "Services/Service.h"
#include "Services/ActiveService.h"
#include "Services/RenderingService.h"
#include "Services/PassiveService.h"
#include <GL/glew.h>
#include <GL/glfw.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <chrono>
#include "Utils/Hash.cpp"
#include "Threads/ThreadPool.h"
#include "Threads/Worker.h"
#include "Utils/Console.h"

#define _THREADS_ 1

class Kernel
{
    public:
        Kernel(ThreadPool* pool, Console* console);
        ~Kernel();

        void start();
        void stop();
        bool isRunning() const;

        void update();
        void render();

        void addActiveService(ActiveService* service);
        void addRenderingService(RenderingService* service);
        void addPassiveService(PassiveService* service);
			
				void sync();

    private:
        std::string _errorMessage;
        bool _isRunning;

        std::vector<ActiveService*> _activeServices;
        std::vector<RenderingService*> _renderingServices;
        std::vector<PassiveService*> _passiveServices;

				ThreadPool* _thread_pool;
				Console* _console;
				
				void setConsoleCommands();
};

#endif
