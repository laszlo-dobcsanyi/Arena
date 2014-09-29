#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define GLEW_STATIC
#include <GL\glew.h>

#include <GLFW/glfw3.h>

#include <SOIL/SOIL.h>

class Texture
{
public:
	GLuint texture;

	Texture(const GLchar* _texturePath);
};

#endif // TEXTURE_H