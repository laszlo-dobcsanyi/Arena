#include <iostream>

#include "MainWindow.h"
#include "Render.h"
#include "InputHandler.hpp"
#include "Shader.h"

MainWindow::MainWindow()
{
	windowWidth = WINDOW_WIDTH;
	windowHeight = WINDOW_HEIGHT;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(windowWidth, windowHeight, "Game", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, &InputHandler::KeyCallback);
	glfwSetMouseButtonCallback(window, &InputHandler::MouseButtonCallback);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, windowWidth, windowHeight);

	render = new Render();
	
	render->InitRender();
}

void MainWindow::DeleteWindow()
{
	glfwTerminate();

	delete render;
}