#include "Render.h"

Render::Render() : TestShader("Shaders\\Model.vs", "Shaders\\Model.frag")
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Render::Draw()
{
	DrawBackground();
	DrawWalls();
	DrawModels();
	DrawProjectiles();
}

void Render::DrawBackground()
{

}

void Render::DrawWalls()
{

}

void Render::DrawModels()
{

}

void Render::DrawProjectiles()
{

}

//TEST
void Render::InitTest()
{
	GLfloat vertices[] = {
		0.5f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f,
		-0.5f, 0.5f
	};
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Render::DrawTest()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	TestShader.Use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}