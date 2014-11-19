#include "Macro"

#include "Stages\Stage_Menu.h"

Stage_Menu::Stage_Menu() : 
	Stage(Stages::MENU),

	disposed(false)
{

}
void Stage_Menu::Render()
{
	Renderer_Menu::Render();
}

void Stage_Menu::Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode)
{
	Renderer_Menu::Handle_Key(_window, _key, _scancode, _action, _mode);
}

void Stage_Menu::Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode)
{
	Renderer_Menu::Handle_Mouse(_window, _key, _action, _mode);
}

void Stage_Menu::Dispose()
{
	if (disposed) return; disposed = true;

	delete this;
}

Stage_Menu::~Stage_Menu()
{

}