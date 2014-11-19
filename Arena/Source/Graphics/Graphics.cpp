#include <assert.h>

#include <boost\foreach.hpp>

#include "Core\Configuration.h"
#include "Graphics\Graphics.h"
#include "Graphics\Shader.h"
#include "Graphics\Camera.h"
#include "Graphics\Texture.h"

namespace Graphics
{
	GLuint Graphics::VAO;
	GLuint Graphics::VBO;
	GLuint Graphics::EBO;

	FT_Library Graphics::font_library;
	FT_Face Graphics::face_outwrite;

	Shader *shaderText;

	GLFWwindow *window;
}

void Graphics::Create()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	assert(Graphics::window = glfwCreateWindow(Configuration::window_width, Configuration::window_height, "Game", nullptr, nullptr));
	glfwMakeContextCurrent(Graphics::window);

	//glfwSetKeyCallback(window, &InputHandler::GameKeyCallback);
	//glfwSetMouseButtonCallback(window, &InputHandler::GameMouseButtonCallback);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, Configuration::window_width, Configuration::window_height);

	shaderText = new Shader("Shaders\\Text.vs", "Shaders\\Text.frag");

	assert(!FT_Init_FreeType(&font_library) && "Could not init freetype library!");
	assert(!FT_New_Face(font_library, "Fonts\\Outwrite.ttf", 0, &face_outwrite) && "Could not open Outwrite font!");
	FT_Set_Pixel_Sizes(face_outwrite, 0, 200);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenVertexArrays(1, &Graphics::VAO);
	glGenBuffers(1, &Graphics::VBO);
	glGenBuffers(1, &Graphics::EBO);
}

void Graphics::Destroy()
{
	glfwTerminate();

	// TODO other stuff too!
}

void Graphics::DrawString(FT_Face *_face, const std::string &_text, float _x, float _y, const float &_sx, const float &_sy)
{
	/*GLint uniform_tex = glGetUniformLocation(shaderText.shaderProgram, "model");

	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	const char *p;

	for (p = _text.c_str(); *p; p++)
	{
	if (FT_Load_Char(*_face, *p, FT_LOAD_RENDER)) continue;
	FT_GlyphSlot g = (*_face)->glyph;

	glTexImage2D(
	GL_TEXTURE_2D,
	0,
	GL_ALPHA,
	g->bitmap.width,
	g->bitmap.rows,
	0,
	GL_ALPHA,
	GL_UNSIGNED_BYTE,
	g->bitmap.buffer
	);

	float x2 = _x + g->bitmap_left * _sx;
	float y2 = -_y - g->bitmap_top * _sy;
	float w = g->bitmap.width * _sx;
	float h = g->bitmap.rows * _sy;

	GLfloat box[4][4] = {
	{ x2, -y2, 0, 0 },
	{ x2 + w, -y2, 1, 0 },
	{ x2, -y2 - h, 0, 1 },
	{ x2 + w, -y2 - h, 1, 1 },
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	_x += (g->advance.x >> 6) * _sx;
	_y += (g->advance.y >> 6) * _sy;
	}*/
}