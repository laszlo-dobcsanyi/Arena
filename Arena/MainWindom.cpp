#include "Render.h"
#include "InputHandler.h"
#include "Shader.h"
#include "MainWindow.h"

MainWindow* MainWindow::mainWindow;
Render* MainWindow::render;
GLFWwindow* MainWindow::window;
GLint MainWindow::windowWidth;
GLint MainWindow::windowHeight;

MainWindow::MainWindow()
{
	windowWidth = WINDOW_WIDTH;
	windowHeight = WINDOW_HEIGHT;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(windowWidth, windowHeight, "Game", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, &InputHandler::GameKeyCallback);
	glfwSetMouseButtonCallback(window, &InputHandler::GameMouseButtonCallback);

	glewExperimental = GL_TRUE;
	glewInit();

	glViewport(0, 0, windowWidth, windowHeight);

	render = new Render();
}

MainWindow* MainWindow::GetMainWindow()
{
	if (mainWindow == 0)
		mainWindow = new MainWindow();
	return mainWindow;
}

void MainWindow::DeleteWindow()
{
	glfwTerminate();

	delete render;
}