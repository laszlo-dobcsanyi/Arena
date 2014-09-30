#ifndef RENDER_H
#define RENDER_H

// GLEW
#define GLEW_STATIC
#include <GL\glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Na ezzel mi a faszt kezdek így
#include "CoreObjects.hpp"
//Ezzel meg végképp
#include "Model.h"

#include "Shader.h"

class Render
{
public:
	Render();

	void Draw();

	void InitTest(); // TEST
	void DrawTest(); // TEST

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

	Shader TestShader; // TEST
};

#endif // RENDER_H