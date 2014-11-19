#ifndef GRAPHICS_RENDERER_LOBBY_H
#define GRAPHICS_RENDERER_LOBBY_H

#include "Graphics\Renderer.h"

class Renderer_Lobby : public Renderer
{
public:
	Renderer_Lobby();
	virtual ~Renderer_Lobby();

	void Render();

	void Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode);
	void Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode);

private:
	Renderer_Lobby(const Renderer_Lobby &_other);
	Renderer_Lobby & operator=(const Renderer_Lobby &_other);
};

#endif