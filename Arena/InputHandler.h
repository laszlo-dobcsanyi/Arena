#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

// GLFW
#include <GLFW/glfw3.h>

#define KEY_ARRAY_MAX_SIZE		4
#define KEY_UP					0
#define KEY_LEFT				1
#define KEY_DOWN				2
#define KEY_RIGHT				3

class InputHandler
{
public:
	static void MenuKeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mode);
	static void MenuMouseButtonCallback(GLFWwindow* _window, int _key, int _action, int _mode);
	static void GameKeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mode);
	static void GameMouseButtonCallback(GLFWwindow* _window, int _key, int _action, int _mode);

private:
	InputHandler() {}

	InputHandler(InputHandler const&);
	void operator=(InputHandler const&);

	static bool keys[KEY_ARRAY_MAX_SIZE];
};

#endif // INPUTHANDLER_HPP