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
class Texture;

namespace Graphics
{
	void Create();
	void Destroy();

	extern GLuint VAO;
	extern GLuint VBO;
	extern GLuint EBO;

	extern GLint viewLoc;
	extern glm::mat4 viewMatrix;
	extern GLint projLoc;
	extern glm::mat4 projectionMatrix;

	extern FT_Library font_library;
	extern FT_Face face_outwrite;

	extern Shader *shaderText;
	extern Texture* font_arial_black;
	
	namespace StringAlignment
	{
		enum Type
		{
			LEFT,
			MIDDLE,
			RIGHT
		};
	};
	void DrawString(const Texture *_font_texture, const std::string &_text, const float &_x, const float &_y, const StringAlignment::Type &_alignment);

	extern GLFWwindow *window;
};
#endif