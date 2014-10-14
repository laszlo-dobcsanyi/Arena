#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

class Shader
{
public:
	Shader(const GLchar* _vertexPath, const GLchar* _fragmentPath);

	void Use() { glUseProgram(shaderProgram); }

	GLuint shaderProgram;
};

#endif // SHDADER_H