#include <boost\foreach.hpp>

#include "Game\Arena.h"
#include "Game\Game.h"
#include "Game\Hero.h"
#include "Game\Wall.h"
#include "Graphics\Render.h"
#include "Graphics\MainWindow.h"
#include "Graphics\Shader.h"
#include "Graphics\Camera.h"
#include "Graphics\Texture.h"

Render::Render() :	shaderWall(new Shader("Shaders\\Wall.vs", "Shaders\\Wall.frag")), 
					shaderHero(new Shader("Shaders\\Hero.vs", "Shaders\\Hero.frag")),	
					shaderText(new Shader("Shaders\\Text.vs", "Shaders\\Text.frag")),
					camera(Camera::GetCamera())
{
	assert(!FT_Init_FreeType(&font_library) && "Could not init freetype library!");
	assert(!FT_New_Face(font_library, "Fonts\\Outwrite.ttf", 0, &face_outwrite) && "Could not open Outwrite font!");
	FT_Set_Pixel_Sizes(face_outwrite, 0, 200);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	projectionMatrix = glm::mat4();
	projectionMatrix = glm::ortho(0.0f, (float)MainWindow::GetWindowWidth(), 0.0f, (float)MainWindow::GetWindowHeight(), CAMERA_VIEW_MIN_DISTANCE, CAMERA_VIEW_MAX_DISTANCE);
}

void Render::InitGameRender() { game = Game::Get(); }

void Render::Draw()
{
	glBindVertexArray(VAO);

	DrawBackground();

	camera->UpdateCameraVectors(game->arena->character->center.x, game->arena->character->center.y);
	
	viewMatrix = glm::lookAt(camera->GetCenterVec(), camera->GetEyeVec(), camera->GetUpVec());

	DrawWalls();
	DrawHeroes();

	glBindVertexArray(0);
	
	// TODO: DrawProjectiles();
}

void Render::DrawBackground()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::DrawWalls()
{
	shaderWall->Use();

	modelLoc = glGetUniformLocation(shaderWall->shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderWall->shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderWall->shaderProgram, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	BOOST_FOREACH(boost::shared_ptr < Wall > wall, game->arena->walls.data.list)
	{
		glBindTexture(GL_TEXTURE_2D, wall->texture->textureID);
		modelMatrix = glm::mat4();

		modelMatrix = glm::translate(modelMatrix, glm::vec3(wall->center.x, wall->center.y, -10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		InitModelShape(wall);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void Render::DrawHeroes()
{
	shaderHero->Use();

	modelLoc = glGetUniformLocation(shaderHero->shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderHero->shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderHero->shaderProgram, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	BOOST_FOREACH(boost::shared_ptr < Hero > hero, game->arena->heroes.data.list)
	{
		glBindTexture(GL_TEXTURE_2D, hero->texture->textureID);
		modelMatrix = glm::mat4();

		modelMatrix = glm::translate(modelMatrix, glm::vec3(hero->center.x, hero->center.y, -10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		InitModelShape(hero);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	glBindTexture(GL_TEXTURE_2D, game->arena->character->texture->textureID);
	modelMatrix = glm::mat4();

	modelMatrix = glm::translate(modelMatrix, glm::vec3(game->arena->character->center.x, game->arena->character->center.y, -10.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	InitModelShape(game->arena->character);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	shaderText->Use();
	DrawString(&face_outwrite, "ZOLKA", 16, 20, 1, 2);
}

void Render::DrawString(FT_Face *_face, const std::string &_text, float _x, float _y, const float &_sx, const float &_sy)
{
	GLint uniform_tex = glGetUniformLocation(shaderHero->shaderProgram, "model");

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
	}
}

void Render::InitModelShape(const boost::shared_ptr< Object > _modelObject)
{
	float shapeWidth = (float)(_modelObject->width);
	float shapeHeight = (float)(_modelObject->height);
	float textureWidthRatio = (float)(shapeWidth * 2 / _modelObject->texture->width);
	float textureHeightRatio = (float)(shapeHeight * 2 / _modelObject->texture->height);

	// TOP RIGHT:
	// Position Coords:
	modelShape.vertices[ 0] =  shapeWidth;
	modelShape.vertices[ 1] =  shapeHeight;

	// Colors:
	modelShape.vertices[ 2] =  1.0f;
	modelShape.vertices[ 3] =  0.0f;
	modelShape.vertices[ 4] =  0.0f;

	// Texture Coords:
	modelShape.vertices[ 5] =  textureWidthRatio;
	modelShape.vertices[ 6] =  textureHeightRatio;
	// ----------------------------

	// BOTTOM RIGHT:
	// Position Coords:
	modelShape.vertices[ 7] =  shapeWidth;
	modelShape.vertices[ 8] = -shapeHeight;

	// Colors:
	modelShape.vertices[ 9] =  0.0f;
	modelShape.vertices[10] =  1.0f;
	modelShape.vertices[11] =  0.0f;

	// Texture Coords:
	modelShape.vertices[12] =  textureWidthRatio;
	modelShape.vertices[13] =  0.0f;
	// ----------------------------

	// BOTTOM LEFT:
	// Position Coords:
	modelShape.vertices[14] = -shapeWidth;
	modelShape.vertices[15] = -shapeHeight;

	// Colors:
	modelShape.vertices[16] =  0.0f;
	modelShape.vertices[17] =  0.0f;
	modelShape.vertices[18] =  1.0f;

	// Texture Coords:
	modelShape.vertices[19] =  0.0f;
	modelShape.vertices[20] =  0.0f;
	// ----------------------------

	// TOP LEFT:
	// Position Coords:
	modelShape.vertices[21] = -shapeWidth;
	modelShape.vertices[22] =  shapeHeight;

	// Colors:
	modelShape.vertices[23] =  1.0f;
	modelShape.vertices[24] =  1.0f;
	modelShape.vertices[25] =  0.0f;

	// Texture Coords:
	modelShape.vertices[26] =  0.0f;
	modelShape.vertices[27] =  textureHeightRatio;
	// ----------------------------

	modelShape.indices[0] = 0;
	modelShape.indices[1] = 1;
	modelShape.indices[2] = 3;
	modelShape.indices[3] = 1;
	modelShape.indices[4] = 2;
	modelShape.indices[5] = 3;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(modelShape.vertices), modelShape.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(modelShape.indices), modelShape.indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}