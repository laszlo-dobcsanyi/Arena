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

void Graphics::DrawString(const FT_Face &_face, const std::string &_text, float _x, float _y, const float &_sx, const float &_sy)
{
	/*const char *p;

	GLsizei width = 0, height = 0;
	for (p = _text.c_str(); *p; p++)
	{
		if (FT_Load_Char(_face, *p, FT_LOAD_RENDER)) continue;
		FT_GlyphSlot g = _face->glyph;
		width += g->bitmap.width;
		height += g->bitmap.rows;
	}

	GLfloat *pixels = new GLfloat[width * height * 4];
	for (int outer = 0; outer < height; ++outer)
		for (int inner = 0; inner < width; ++inner)
		{
			pixels[outer * height + inner + 0] = outer * inner * 1;
			pixels[outer * height + inner + 1] = outer * inner * 2;
			pixels[outer * height + inner + 2] = outer * inner * 3;
			pixels[outer * height + inner + 3] = outer * inner * 4;
		}

	glDrawPixels(width, height, GL_RGBA, GL_FLOAT, pixels);
	glfwSwapBuffers(Graphics::window);

	delete[] pixels;*/
}