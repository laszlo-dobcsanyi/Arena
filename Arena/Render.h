#ifndef RENDER_H
#define RENDER_H

//GLEW
#define GLEW_STATIC
#include <GL\glew.h>

//GLFW
#include <GLFW/glfw3.h>

class Render
{
public:
	Render();

	void Draw();

	GLuint& GetVAO() { return VAO; }
	GLuint& GetVBO() { return VBO; }
	GLuint& GetEBO() { return EBO; }

private:
	void DrawBackground();
	void DrawObjects();
	void DrawModells();
	void DrawProjectiles();

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};

#endif // RENDER_H