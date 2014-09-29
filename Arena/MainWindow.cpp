#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL\glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include "MainWindow.h"
#include "InputHandler.hpp"

MainWindow::MainWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Game", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, &InputHandler::KeyCallback);
	glfwSetMouseButtonCallback(window, &InputHandler::MouseButtonCallback);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, 800, 600);

	InitObjects();

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
}

void MainWindow::InitObjects()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}