#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <GLFW/glfw3.h>

class InputHandler
{
public:

	// GLFW KeyCallback
	static void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mode)
	{
		if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(_window, GL_TRUE);
		}
	}

	// GLFW MouseButtonCallback
	static void MouseButtonCallback(GLFWwindow* _window, int _key, int _action, int _mode)
	{
		if (_key == GLFW_MOUSE_BUTTON_1 && _action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(_window, GL_TRUE);
		}
	}

private:
	InputHandler() {}

	// Prevent copies and assignments
	InputHandler(InputHandler const&);
	void operator=(InputHandler const&);
};

#endif // INPUTHANDLER_HPP