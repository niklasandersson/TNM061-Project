#ifndef TEXTSERVICE_H
#define TEXTSERVICE_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <iostream>
#include "RenderingService.h"
#include "../Utils/Shader.h"
#include "../Handles/TextHandle.h"

class TextService : public RenderingService
{
	public:
		TextService(std::string texturePath);
		~TextService();

		void render();
		void update();

		void changeText(std::string text);

		TextHandle* getTextHandle();

	private:
		unsigned int _textureID;
		unsigned int _shaderID;
		unsigned int _vertexBufferID;
		unsigned int _uvBufferID;
		unsigned int _textureUniformID;

		glm::vec2* _vertexBuffer;
		glm::vec2* _uvBuffer;
		TextHandle* _textHandle;

		int _textLength;
		int _size;


};

#endif