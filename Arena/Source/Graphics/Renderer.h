#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

class Renderer
{
public:
	virtual void Render() = 0;

	virtual void Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode) = 0;
	virtual void Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode) = 0;
};

#endif // RENDER_H