#ifndef RENDER_H
#define RENDER_H

// GLEW
#define GLEW_STATIC
#include <GL\glew.h>
#include <vector>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"
#include "Shader.h"
#include "Platform.h"
#include "Camera.h"

class Render
{
public:
	Render();

	void Draw();

	void InitTest(); // TEST
	void DrawTest(); // TEST
	void AddPlatform(const float& _xPos, const float& _yPos, const float& width, const float& height); // TEST
	void AddModel(const float& _xPos, const float& _yPos); // TEST

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

	// TEST
	GLfloat vertices[8];
	GLuint indices[6];
	Shader shaderModel;
	Shader shaderPlatform;
	Model model;
	std::vector<Platform> platformsVector;
	std::vector<Model> modelsVector;
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	GLint modelLoc;
	GLint viewLoc;
	GLint projLoc;
};

#endif // RENDER_H