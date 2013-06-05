#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include "../Utils/Shader.h"

#include <string>
#include <iostream>

class ShaderObject
{
	public:
		ShaderObject(std::string vertexShaderName, std::string fragmentShaderName);

		GLuint getShaderProgram();
	private:
		std::string _vertexShaderName;
		std::string _fragmentShaderName;

		GLuint _shaderProgram;

};

#endif