#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// GLEW
#define GLEW_STATIC
#include <GL\glew.h>

// GLFW
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH		1280
#define WINDOW_HEIGHT		720

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

	GLint windowWidth;
	GLint windowHeight;
};


#endif // MAINWINDOW_H