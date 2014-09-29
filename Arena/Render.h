#ifndef RENDER_H
#define RENDER_H

//GLEW
#define GLEW_STATIC
#include <GL\glew.h>

//GLFW
#include <GLFW/glfw3.h>

//Na ezzel mi a faszt kezdek �gy
#include "CoreObjects.hpp"
//Ezzel meg v�gk�pp
#include "Model.h"

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
	void DrawWalls();
	void DrawModels();
	void DrawProjectiles();

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};

#endif // RENDER_H