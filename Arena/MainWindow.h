#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// GLEW
#define GLEW_STATIC
#include <GL\glew.h>

// GLFW
#include <GLFW/glfw3.h>

class Render;

class MainWindow
{
public:
	MainWindow();
	
	GLFWwindow* const GetWindow() { return window; }
	Render* const GetRender() { return render; }
	void DeleteWindow();

private:
	Render* render;
	GLFWwindow* window;
};


#endif // MAINWINDOW_H