#ifndef GRAPHICS_GRAPHICS_H
#define GRAPHICS_GRAPHICS_H

#include <string>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#define OPENGL_MAJOR_VERSION	3
#define OPENGL_MINOR_VERSION	3

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

class Shader;

namespace Graphics
{
	void Create();
	void Destroy();

	extern GLuint VAO;
	extern GLuint VBO;
	extern GLuint EBO;

	extern FT_Library font_library;
	extern FT_Face face_outwrite;

	extern Shader *shaderText;
	void DrawString(FT_Face *_face, const std::string &_text, float _x, float _y, const float &_sx, const float &_sy);

	extern GLFWwindow *window;
};
#endif