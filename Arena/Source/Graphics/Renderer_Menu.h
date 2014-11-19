#ifndef GRAPHICS_RENDERER_MENU_H
#define GRAPHICS_RENDERER_MENU_H

#include "Graphics\Renderer.h"

class Renderer_Menu : public Renderer
{
public:
	Renderer_Menu();
	virtual ~Renderer_Menu();

	void Render();

	void Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode);
	void Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode);

private:
	Renderer_Menu(const Renderer_Menu &_other);
	Renderer_Menu & operator=(const Renderer_Menu &_other);
};
#endif