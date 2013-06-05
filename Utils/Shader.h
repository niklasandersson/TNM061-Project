#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GL/glfw.h>

GLuint LoadShaders(const char* vsPath, const char* fsPath);

#endif

