#ifndef RENDER_H
#define RENDER_H

#include <forward_list>

#include <boost\shared_ptr.hpp>

// GLEW
#define GLEW_STATIC
#include <GL\glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

class ModelObject;

struct ModelMainShape
{
	GLfloat vertices[8];
	GLuint indices[6];

	ModelMainShape()
	{
		vertices[0] = 0.5f;
		vertices[1] = 0.5f;
		vertices[2] = 0.5f;
		vertices[3] = -0.5f;
		vertices[4] = -0.5f;
		vertices[5] = -0.5f;
		vertices[6] = -0.5f;
		vertices[7] = 0.5f;

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 3;
		indices[3] = 1;
		indices[4] = 2;
		indices[5] = 3;
	}
};

class Render
{
public:
	Render();

	void Draw();
	void InitRender();
	void AddHero(const float& _xPos, const float& _yPos);
	void AddWall(const float& _xPos, const float& _yPos, const float& width, const float& height);

	GLuint& GetVAO() { return VAO; }
	GLuint& GetVBO() { return VBO; }
	GLuint& GetEBO() { return EBO; }

private:
	void DrawBackground();
	void DrawHeroes();
	void DrawWalls();
	// TODO: void DrawProjectiles();

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Shader shaderModel;
	Shader shaderPlatform;
	ModelMainShape modelMainShape;
	std::forward_list< boost::shared_ptr< ModelObject > > heroes;
	std::forward_list< boost::shared_ptr< ModelObject > > walls;
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	GLint modelLoc;
	GLint viewLoc;
	GLint projLoc;
};

#endif // RENDER_H