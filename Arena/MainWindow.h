#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//GLEW
#define GLEW_STATIC
#include <GL\glew.h>

//GLFW
#include <GLFW/glfw3.h>

class MainWindow
{
public:
	MainWindow();

	void InitObjects();

	GLuint& GetVAO() { return VAO; }
	GLuint& GetVBO() { return VBO; }
	GLuint& GetEBO() { return EBO; }

private:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};


#endif //MAINWINDOW_H