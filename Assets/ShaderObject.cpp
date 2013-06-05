#include "ShaderObject.h"

ShaderObject::ShaderObject(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	_shaderProgram = LoadShaders(vertexShaderPath.c_str(),fragmentShaderPath.c_str());
}

GLuint ShaderObject::getShaderProgram()
{
	return _shaderProgram;
}