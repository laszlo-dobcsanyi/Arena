#include "Macro"

#include "Graphics\Graphics.h"
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
	if (_action == GLFW_PRESS)
	{
		switch (_key)
		{
		case GLFW_KEY_ENTER:
			switch (current)
			{
			case 0: Stage_Handler::SetStage(Stages::LOCAL); return;
			case 1: Stage_Handler::SetStage(Stages::CLIENT); return;
			case 2: Stage_Handler::SetStage(Stages::SERVER); return;
			case 3: return; // TODO OPTIONS
			case 4: glfwSetWindowShouldClose(Graphics::window, GL_TRUE); return;
			}
			break;
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(Graphics::window, GL_TRUE); break;
		}
	}

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