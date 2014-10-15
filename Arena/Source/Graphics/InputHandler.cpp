#include <cstdint>

#include "Source\Game\Game.h"
#include "Source\Game\Arena.h"
#include "Source\Game\Hero.h"
#include "Source\Graphics\InputHandler.h"

bool InputHandler::keys[KEY_ARRAY_MAX_SIZE];

void MenuKeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mode)
{
	// Placeholder
}

void MenuMouseButtonCallback(GLFWwindow* _window, int _key, int _action, int _mode)
{
	// Placeholder
}

void InputHandler::GameKeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mode)
{
	switch (_key)
	{
		case GLFW_KEY_W:
		{
			keys[KEY_UP] = (_action == GLFW_PRESS ? true : (_action == GLFW_RELEASE ? false : keys[KEY_UP]));
			break;
		}

		case GLFW_KEY_A:
		{
			keys[KEY_LEFT] = (_action == GLFW_PRESS ? true : (_action == GLFW_RELEASE ? false : keys[KEY_LEFT]));
			break;
		}

		case GLFW_KEY_S:
		{
			keys[KEY_DOWN] = (_action == GLFW_PRESS ? true : (_action == GLFW_RELEASE ? false : keys[KEY_DOWN]));
			break;
		}

		case GLFW_KEY_D:
		{
			keys[KEY_RIGHT] = (_action == GLFW_PRESS ? true : (_action == GLFW_RELEASE ? false : keys[KEY_RIGHT]));
			break;
		}
		case GLFW_KEY_SPACE:
		{
			keys[KEY_JUMP] = (_action == GLFW_PRESS ? true : (_action == GLFW_RELEASE ? false : keys[KEY_JUMP]));
			break;
		}
	}

	if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(_window, GL_TRUE);
	}

	if (_action == GLFW_PRESS || _action == GLFW_RELEASE) GameMovement();
}

void InputHandler::GameMouseButtonCallback(GLFWwindow* _window, int _key, int _action, int _mode)
{
	/*if (_key == GLFW_MOUSE_BUTTON_1 && _action == GLFW_PRESS)
	{
	glfwSetWindowShouldClose(_window, GL_TRUE);
	}*/
}

void InputHandler::GameMovement()
{
	uint8_t movement = 0x0000000;

	movement |= Hero_Movement::RIGHT * keys[KEY_RIGHT];
	movement |= Hero_Movement::DOWN * keys[KEY_DOWN];
	movement |= Hero_Movement::LEFT * keys[KEY_LEFT];
	movement |= Hero_Movement::UP * keys[KEY_UP];
	movement |= Hero_Movement::JUMP * keys[KEY_JUMP];
	
	Game::Get()->arena->character->Move(movement);
}