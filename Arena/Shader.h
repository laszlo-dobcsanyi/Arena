#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
class Shader
{
public:
	GLuint shaderProgram;

	Shader(const GLchar* _vertexPath, const GLchar* _fragmentPath);

	void Use() { glUseProgram(this->shaderProgram); }
};

#endif // SHDADER_H