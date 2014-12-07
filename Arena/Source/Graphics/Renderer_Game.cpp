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


	camera(Camera::GetCamera())
{
	Graphics::shader_wall = new Shader("Shaders\\Wall.vs", "Shaders\\Wall.frag");
	Graphics::shader_hero = new Shader("Shaders\\Hero.vs", "Shaders\\Hero.frag");
}

Renderer_Game::~Renderer_Game()
{
	delete Graphics::shader_wall;
	delete Graphics::shader_hero;
}

void Renderer_Game::Render()
{
	if (game)
	{
		glBindVertexArray(Graphics::VAO);

		Hero_Descriptor character_current = game->arena->character->states.Current_Copy();
		camera->UpdateCameraVectors(character_current.center.x, character_current.center.y);

		Graphics::viewMatrix = glm::lookAt(camera->GetCenterVec(), camera->GetEyeVec(), camera->GetUpVec());

		DrawBackground();
		DrawWalls();
		DrawHeroes(character_current);
	
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
	Graphics::shader_wall->Use();

	//
	Graphics::viewLoc = glGetUniformLocation(Graphics::shader_wall->shaderProgram, "view");
	Graphics::projLoc = glGetUniformLocation(Graphics::shader_wall->shaderProgram, "projection");

	glUniformMatrix4fv(Graphics::viewLoc, 1, GL_FALSE, glm::value_ptr(Graphics::viewMatrix));
	glUniformMatrix4fv(Graphics::projLoc, 1, GL_FALSE, glm::value_ptr(Graphics::projectionMatrix));

	BOOST_FOREACH(boost::shared_ptr < Wall > wall, game->arena->walls.data.list)
	{
		wall->Draw(*wall);
	}
}

void Renderer_Game::DrawHeroes(const Hero_Descriptor &_character)
{
	Graphics::shader_hero->Use();

	//modelLoc = glGetUniformLocation(shaderHero->shaderProgram, "model");
	Graphics::viewLoc = glGetUniformLocation(Graphics::shader_hero->shaderProgram, "view");
	Graphics::projLoc = glGetUniformLocation(Graphics::shader_hero->shaderProgram, "projection");

	glUniformMatrix4fv(Graphics::viewLoc, 1, GL_FALSE, glm::value_ptr(Graphics::viewMatrix));
	glUniformMatrix4fv(Graphics::projLoc, 1, GL_FALSE, glm::value_ptr(Graphics::projectionMatrix));

	BOOST_FOREACH(boost::shared_ptr < Hero > hero, game->arena->heroes.data.list)
	{
		hero->Draw(*(hero->states.Current()));
	}

	game->arena->character->Draw(_character);
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

