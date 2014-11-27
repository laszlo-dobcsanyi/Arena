#include "Macro"

#include <string>
#include <iostream>

#include "Core\Configuration.h"
#include "Graphics\Camera.h"
#include "Graphics\Graphics.h"
#include "Graphics\Renderer_Menu.h"
#include "Stages\Stage_Handler.h"

Renderer_Menu::Renderer_Menu()
{
	Camera::GetCamera()->UpdateCameraVectors(Configuration::window_width / 2.0f, Configuration::window_height / 2.0f);
	Graphics::viewMatrix = glm::lookAt(Camera::GetCamera()->GetCenterVec(), Camera::GetCamera()->GetEyeVec(), Camera::GetCamera()->GetUpVec());
}

Renderer_Menu::~Renderer_Menu()
{

}

void Renderer_Menu::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(Graphics::VAO);

	static const float center_x = Configuration::window_width / 2.0f;
	static const float center_y = 200.f;

	Graphics::DrawString(Graphics::font_arial_black, ">> Arena <<", center_x, Configuration::window_height - 2 * 32.0f, Graphics::StringAlignment::MIDDLE);

	Graphics::DrawString(Graphics::font_arial_black, (current == 0 ? ">Local Game" : "Local Game"), center_x, center_y + 4 * 48.f, Graphics::StringAlignment::MIDDLE);
	Graphics::DrawString(Graphics::font_arial_black, (current == 1 ? ">Join Network Game" : "Join Network Game"), center_x, center_y + 3 * 48.f, Graphics::StringAlignment::MIDDLE);
	Graphics::DrawString(Graphics::font_arial_black, (current == 2 ? ">Host Network Game" : "Host Network Game"), center_x, center_y + 2 * 48.f, Graphics::StringAlignment::MIDDLE);
	Graphics::DrawString(Graphics::font_arial_black, (current == 3 ? ">Options" : "Options"), center_x, center_y + 1 * 48.f, Graphics::StringAlignment::MIDDLE);
	Graphics::DrawString(Graphics::font_arial_black, (current == 4 ? ">Exit" : "Exit"), center_x, center_y + 0 * 48.f, Graphics::StringAlignment::MIDDLE);

	glBindVertexArray(0);

}

void Renderer_Menu::Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode)
{
	if (_action == GLFW_PRESS)
	{
		switch (_key)
		{
		case GLFW_KEY_W: current = (0 < current ? current - 1 : 5 - 1); break;
		case GLFW_KEY_S: current = (current < 5 - 1 ? current + 1 : 0); break;
		}
	}

}

void Renderer_Menu::Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode)
{

}