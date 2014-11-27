#include "Macro"

#include <cstdint>

#include "Core\Configuration.h"
#include "Game\Arena.h"
#include "Game\Game.h"
#include "Game\Hero.h"
#include "Game\Wall.h"
#include "Graphics\Graphics.h"
#include "Graphics\Camera.h"
#include "Graphics\Shader.h"
#include "Graphics\Texture.h"
#include "Graphics\Renderer_Game.h"
#include "Stages\Stage_Handler.h"

Renderer_Game::Renderer_Game(Game *_game) :
	game(_game),

	shaderWall(new Shader("Shaders\\Wall.vs", "Shaders\\Wall.frag")),
	shaderHero(new Shader("Shaders\\Hero.vs", "Shaders\\Hero.frag")),

	camera(Camera::GetCamera())

{

}

Renderer_Game::~Renderer_Game()
{

}

void Renderer_Game::Render()
{
	if (game)
	{
		glBindVertexArray(Graphics::VAO);

		camera->UpdateCameraVectors(game->arena->character->center.x, game->arena->character->center.y);
		Graphics::viewMatrix = glm::lookAt(camera->GetCenterVec(), camera->GetEyeVec(), camera->GetUpVec());

		DrawBackground();
		DrawWalls();
		DrawHeroes();
	
		//Graphics::DrawString(Graphics::font_arial_black, "Lacko", game->arena->character->center.x, game->arena->character->center.y);
		glBindVertexArray(0);
	}
	else
	{
		// TODO draw loading!
	}
}

void Renderer_Game::DrawBackground()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer_Game::DrawWalls()
{
	shaderWall->Use();

	modelLoc = glGetUniformLocation(shaderWall->shaderProgram, "model");
	Graphics::viewLoc = glGetUniformLocation(shaderWall->shaderProgram, "view");
	Graphics::projLoc = glGetUniformLocation(shaderWall->shaderProgram, "projection");

	glUniformMatrix4fv(Graphics::viewLoc, 1, GL_FALSE, glm::value_ptr(Graphics::viewMatrix));
	glUniformMatrix4fv(Graphics::projLoc, 1, GL_FALSE, glm::value_ptr(Graphics::projectionMatrix));

	BOOST_FOREACH(boost::shared_ptr < Wall > wall, game->arena->walls.data.list)
	{
		DrawObject(wall);
	}
}

void Renderer_Game::DrawHeroes()
{
	shaderHero->Use();

	modelLoc = glGetUniformLocation(shaderHero->shaderProgram, "model");
	Graphics::viewLoc = glGetUniformLocation(shaderHero->shaderProgram, "view");
	Graphics::projLoc = glGetUniformLocation(shaderHero->shaderProgram, "projection");

	glUniformMatrix4fv(Graphics::viewLoc, 1, GL_FALSE, glm::value_ptr(Graphics::viewMatrix));
	glUniformMatrix4fv(Graphics::projLoc, 1, GL_FALSE, glm::value_ptr(Graphics::projectionMatrix));

	BOOST_FOREACH(boost::shared_ptr < Hero > hero, game->arena->heroes.data.list)
	{
		DrawObject(hero);
	}

	DrawObject(game->arena->character);
}

void Renderer_Game::DrawObject(const boost::shared_ptr< Object > _object)
{
	glBindTexture(GL_TEXTURE_2D, _object->texture->textureID);
	modelMatrix = glm::mat4();

	modelMatrix = glm::translate(modelMatrix, glm::vec3(_object->center.x, _object->center.y, -10.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	float shapeWidth = (float)(_object->width);
	float shapeHeight = (float)(_object->height);
	float textureWidthRatio = (float)(shapeWidth * 2 / _object->texture->width);
	float textureHeightRatio = (float)(shapeHeight * 2 / _object->texture->height);

	// TOP RIGHT:
	// Position Coords:
	modelShape.vertices[0] = shapeWidth;
	modelShape.vertices[1] = shapeHeight;

	// Colors:
	modelShape.vertices[2] = 1.0f;
	modelShape.vertices[3] = 0.0f;
	modelShape.vertices[4] = 0.0f;

	// Texture Coords:
	modelShape.vertices[5] = textureWidthRatio;
	modelShape.vertices[6] = textureHeightRatio;
	// ----------------------------

	// BOTTOM RIGHT:
	// Position Coords:
	modelShape.vertices[7] = shapeWidth;
	modelShape.vertices[8] = -shapeHeight;

	// Colors:
	modelShape.vertices[9] = 0.0f;
	modelShape.vertices[10] = 1.0f;
	modelShape.vertices[11] = 0.0f;

	// Texture Coords:
	modelShape.vertices[12] = textureWidthRatio;
	modelShape.vertices[13] = 0.0f;
	// ----------------------------

	// BOTTOM LEFT:
	// Position Coords:
	modelShape.vertices[14] = -shapeWidth;
	modelShape.vertices[15] = -shapeHeight;

	// Colors:
	modelShape.vertices[16] = 0.0f;
	modelShape.vertices[17] = 0.0f;
	modelShape.vertices[18] = 1.0f;

	// Texture Coords:
	modelShape.vertices[19] = 0.0f;
	modelShape.vertices[20] = 0.0f;
	// ----------------------------

	// TOP LEFT:
	// Position Coords:
	modelShape.vertices[21] = -shapeWidth;
	modelShape.vertices[22] = shapeHeight;

	// Colors:
	modelShape.vertices[23] = 1.0f;
	modelShape.vertices[24] = 1.0f;
	modelShape.vertices[25] = 0.0f;

	// Texture Coords:
	modelShape.vertices[26] = 0.0f;
	modelShape.vertices[27] = textureHeightRatio;
	// ----------------------------

	modelShape.indices[0] = 0;
	modelShape.indices[1] = 1;
	modelShape.indices[2] = 3;
	modelShape.indices[3] = 1;
	modelShape.indices[4] = 2;
	modelShape.indices[5] = 3;

	glBindBuffer(GL_ARRAY_BUFFER, Graphics::VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(modelShape.vertices), modelShape.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Graphics::EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(modelShape.indices), modelShape.indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

//

void Renderer_Game::Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode)
{
	if (game)
	{
		switch (_key)
		{
		case GLFW_KEY_W: keys[Game_Keys::KEY_UP] = (_action == GLFW_PRESS ? true : (_action == GLFW_RELEASE ? false : keys[Game_Keys::KEY_UP])); break;
		case GLFW_KEY_A: keys[Game_Keys::KEY_LEFT] = (_action == GLFW_PRESS ? true : (_action == GLFW_RELEASE ? false : keys[Game_Keys::KEY_LEFT])); break;
		case GLFW_KEY_S: keys[Game_Keys::KEY_DOWN] = (_action == GLFW_PRESS ? true : (_action == GLFW_RELEASE ? false : keys[Game_Keys::KEY_DOWN])); break;
		case GLFW_KEY_D: keys[Game_Keys::KEY_RIGHT] = (_action == GLFW_PRESS ? true : (_action == GLFW_RELEASE ? false : keys[Game_Keys::KEY_RIGHT])); break;
		case GLFW_KEY_SPACE: keys[Game_Keys::KEY_JUMP] = (_action == GLFW_PRESS ? true : (_action == GLFW_RELEASE ? false : keys[Game_Keys::KEY_JUMP])); break;
		}

		if (_action == GLFW_PRESS || _action == GLFW_RELEASE)
		{
			uint8_t movement = 0x0000000;

			movement |= Hero_Movement::RIGHT * keys[Game_Keys::KEY_RIGHT];
			movement |= Hero_Movement::DOWN * keys[Game_Keys::KEY_DOWN];
			movement |= Hero_Movement::LEFT * keys[Game_Keys::KEY_LEFT];
			movement |= Hero_Movement::UP * keys[Game_Keys::KEY_UP];
			movement |= Hero_Movement::JUMP * keys[Game_Keys::KEY_JUMP];

			game->arena->character->Move(movement);
			BOOST_FOREACH(boost::shared_ptr< Hero > hero, game->arena->heroes.data.list)
			{
				hero->Move(movement);
			}
		}
	}
	else
	{
	}

	if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS) Stage_Handler::SetStage(Stages::MENU);
}

void Renderer_Game::Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode)
{
	if (game)
	{

	}
	else
	{

	}
}

