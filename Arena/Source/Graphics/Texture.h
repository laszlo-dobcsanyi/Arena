#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//SOIL
#include <SOIL/SOIL.h>

#include <ft2build.h>
#include FT_FREETYPE_H

class Texture
{
public:
	Texture(const GLchar* _texturePath);

	GLuint textureID;
	int width;
	int height;
};
#endif // TEXTURE_H