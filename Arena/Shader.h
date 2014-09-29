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
	GLuint ShaderProgram;

	Shader(const GLchar* _vertexPath, const GLchar* _fragmentPath);

	void Use() { glUseProgram(this->ShaderProgram); }
};

#endif //SHDADER_H