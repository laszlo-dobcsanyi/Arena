#include "Macro"

#include <iostream>

#include "Graphics\Renderer_Menu.h"
#include "Stages\Stage_Handler.h"

Renderer_Menu::Renderer_Menu()
{

}

Renderer_Menu::~Renderer_Menu()
{

}

void Renderer_Menu::Render()
{
	std::cout << ">> MENU <<\n1)LOCAL\n2)CLIENT\n3)SERVER\n";
	char c = std::cin.get();
	switch (c)
	{
	case '1': Stage_Handler::SetStage(Stages::LOCAL); break;
	case '2': Stage_Handler::SetStage(Stages::CLIENT); break;
	case '3': Stage_Handler::SetStage(Stages::SERVER); break;
	}
}

void Renderer_Menu::Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode)
{

}

void Renderer_Menu::Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode)
{

}