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

class Render
{
public:
	Render();

	void Draw();

	void InitTest(); // TEST
	void DrawTest(); // TEST
	void AddPlatform(const float& _xPos, const float& _yPos, const float& width, const float& height); // TEST

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
	Shader TestShaderModel;
	Shader TestShaderPlatform;
	Model TestModel;
	std::vector<Platform> TestPlatforms;
	glm::mat4 TestModelMat4;
	glm::mat4 TestViewMat4;
	glm::mat4 TestProjectionMat4;
	GLint TestModelLoc;
	GLint TestViewLoc;
	GLint TestProjLoc;
};

#endif // RENDER_H