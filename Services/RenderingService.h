#ifndef RENDERINGSERVICE_H
#define RENDERINGSERVICE_H

#include "ActiveService.h"


class RenderingService : public ActiveService
{

	public:
		RenderingService(std::string name);
		virtual void render() = 0;
		bool isRendering();

	protected:
		void startRendering();
		void stopRendering();

	private:
		int _renderingPriority;

};

#endif