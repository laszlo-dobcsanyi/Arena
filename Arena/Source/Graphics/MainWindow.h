#ifndef GRAPHICS_MAINWINDOW_H
#define GRAPHICS_MAINWINDOW_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#define OPENGL_MAJOR_VERSION	3
#define OPENGL_MINOR_VERSION	3
#define WINDOW_WIDTH			1280
#define WINDOW_HEIGHT			720

class Render;

class MainWindow
{
public:
	static MainWindow* GetMainWindow();
	static Render* GetRender() { return render; }
	static GLFWwindow* GetWindow() { return window; }
	static GLint& GetWindowWidth() { return windowWidth; }
	static GLint& GetWindowHeight() { return windowHeight; }
	static void MainWindow::DeleteWindow();

private:
	MainWindow();

	MainWindow(MainWindow const&);
	void operator=(MainWindow const&);

	static MainWindow* mainWindow;
	static Render* render;
	static GLFWwindow* window;
	static GLint windowWidth;
	static GLint windowHeight;
};

#endif // MAINWINDOW_H