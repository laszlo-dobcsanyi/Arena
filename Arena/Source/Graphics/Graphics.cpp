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

	GLint viewLoc;
	glm::mat4 viewMatrix;
	GLint projLoc;
	glm::mat4 projectionMatrix;

	FT_Library Graphics::font_library;
	FT_Face Graphics::face_outwrite;

	Texture* font_arial_black;
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
	font_arial_black = new Texture("Fonts\\arial_black.png");

	assert(!FT_Init_FreeType(&font_library) && "Could not init freetype library!");
	assert(!FT_New_Face(font_library, "Fonts\\Outwrite.ttf", 0, &face_outwrite) && "Could not open Outwrite font!");
	FT_Set_Pixel_Sizes(face_outwrite, 0, 16);

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);*/

	Graphics::projectionMatrix = glm::mat4();
	Graphics::projectionMatrix = glm::ortho(0.0f, (float)Configuration::window_width, 0.0f, (float)Configuration::window_height, Configuration::camera_min_distance, Configuration::camera_max_distance);

	glGenVertexArrays(1, &Graphics::VAO);
	glGenBuffers(1, &Graphics::VBO);
	glGenBuffers(1, &Graphics::EBO);
}

void Graphics::Destroy()
{
	glfwTerminate();

	// TODO other stuff too!
}

void Graphics::DrawString(const Texture *_font_texture, const std::string &_text, const float &_x, const float &_y, const StringAlignment::Type &_alignment)
{
	static const unsigned int glyph_count = 16;

	shaderText->Use();

	GLint modelLoc = glGetUniformLocation(shaderText->shaderProgram, "model");
	projLoc = glGetUniformLocation(shaderText->shaderProgram, "projection");
	viewLoc = glGetUniformLocation(shaderText->shaderProgram, "view");

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glBindTexture(GL_TEXTURE_2D, _font_texture->textureID);

	float glyph_Width = (float)_font_texture->width / glyph_count;
	float glyph_Height = (float)_font_texture->height / glyph_count;
	float glyph_WidthRatio = 1.0 / glyph_count;
	float glyph_HeightRatio = 1.0 / glyph_count;

	float calculated_x = _x;
	switch (_alignment)
	{
	case StringAlignment::LEFT: break;
	case StringAlignment::MIDDLE: calculated_x -= (_text.length() * glyph_Width) / 2.0f; break;
	case StringAlignment::RIGHT: calculated_x -= _text.length() * glyph_Width; break;
	}

	for (unsigned int current = 0; current < _text.length(); current++)
	{
		float glyph_x = (float)(_text[current] % glyph_count);
		float glyph_y = (float)glyph_count - _text[current] / glyph_count - 1;

		glm::mat4 modelMatrix = glm::mat4();
		modelMatrix = glm::translate(modelMatrix, glm::vec3(calculated_x + glyph_Width * current, _y, -5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		struct GlyphShape
		{
		public:
			GLfloat vertices[28];
			GLuint indices[6];
		} glyph;

		// TOP RIGHT:
		// Position Coords:
		glyph.vertices[0] = glyph_Width;
		glyph.vertices[1] = glyph_Height;

		// Colors:
		glyph.vertices[2] = 1.0f;
		glyph.vertices[3] = 0.0f;
		glyph.vertices[4] = 0.0f;

		// Texture Coords:
		glyph.vertices[5] = (glyph_x + 1) * glyph_WidthRatio;
		glyph.vertices[6] = (glyph_y + 1) * glyph_HeightRatio;
		// ----------------------------

		// BOTTOM RIGHT:
		// Position Coords:
		glyph.vertices[7] = glyph_Width;
		glyph.vertices[8] = 0.0f;

		// Colors:
		glyph.vertices[9] = 0.0f;
		glyph.vertices[10] = 1.0f;
		glyph.vertices[11] = 0.0f;

		// Texture Coords:
		glyph.vertices[12] = (glyph_x + 1) * glyph_WidthRatio;
		glyph.vertices[13] = (glyph_y + 0) * glyph_HeightRatio;
		// ----------------------------

		// BOTTOM LEFT:
		// Position Coords:
		glyph.vertices[14] = 0.0f;
		glyph.vertices[15] = 0.0f;

		// Colors:
		glyph.vertices[16] = 0.0f;
		glyph.vertices[17] = 0.0f;
		glyph.vertices[18] = 1.0f;

		// Texture Coords:
		glyph.vertices[19] = (glyph_x + 0) * glyph_WidthRatio;
		glyph.vertices[20] = (glyph_y + 0) * glyph_HeightRatio;
		// ----------------------------

		// TOP LEFT:
		// Position Coords:
		glyph.vertices[21] = 0.0f;
		glyph.vertices[22] = glyph_Height;

		// Colors:
		glyph.vertices[23] = 1.0f;
		glyph.vertices[24] = 1.0f;
		glyph.vertices[25] = 0.0f;

		// Texture Coords:
		glyph.vertices[26] = (glyph_x + 0) * glyph_WidthRatio;
		glyph.vertices[27] = (glyph_y + 1) * glyph_HeightRatio;
		// ----------------------------

		glyph.indices[0] = 0;
		glyph.indices[1] = 1;
		glyph.indices[2] = 3;
		glyph.indices[3] = 1;
		glyph.indices[4] = 2;
		glyph.indices[5] = 3;

		glBindBuffer(GL_ARRAY_BUFFER, Graphics::VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glyph.vertices), glyph.vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Graphics::EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glyph.indices), glyph.indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}