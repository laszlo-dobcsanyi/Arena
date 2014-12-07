#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

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
	GLuint shaderProgram;

	Shader(const GLchar* _vertexPath, const GLchar* _fragmentPath);
	~Shader();

	void Use() const { glUseProgram(shaderProgram); }

private:
	Shader(const Shader &_other);
	Shader operator=(const Shader &_other);
};

#endif // SHDADER_H