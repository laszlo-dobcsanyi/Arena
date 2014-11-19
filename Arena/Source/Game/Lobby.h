#ifndef GAME_LOBBY_H
#define GAME_LOBBY_H

#include <boost\atomic.hpp>

#include "Graphics\Renderer.h"

class Lobby : public Renderer
{
public:
	Lobby();

	void Render();

	void Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode);
	void Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode);

	void Dispose();
	virtual ~Lobby();

private:
	boost::atomic< bool > disposed;

	Lobby(const Lobby &_other);
	Lobby & operator=(const Lobby &_other);
};
#endif