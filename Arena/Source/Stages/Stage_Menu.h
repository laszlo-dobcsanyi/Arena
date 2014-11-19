#ifndef STAGES_STAGE_MENU_H
#define STAGES_STAGE_MENU_H

#include <boost\atomic.hpp>

#include "Graphics\Renderer_Menu.h"
#include "Stages\Stage.h"

class Stage_Menu : public Stage, public Renderer_Menu
{
public:
	Stage_Menu();

	void Render();

	void Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode);
	void Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode);

	void Dispose();

private:
	boost::atomic< bool > disposed;
	~Stage_Menu();

	Stage_Menu(const Stage_Menu &_other);
	Stage_Menu & operator=(const Stage_Menu &_other);
};
#endif