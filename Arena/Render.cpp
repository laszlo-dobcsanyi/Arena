#include "Render.h"

Render::Render() :	shaderModel("Shaders\\Model.vs", "Shaders\\Model.frag"),
					shaderPlatform("Shaders\\Platform.vs", "Shaders\\Platform.frag"),
					model()
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
	glBindVertexArray(VAO);

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

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	AddModel(1.0f, 1.0f);
	AddPlatform(0.0f, 0.0f, 0.5f, 0.5f);
	AddPlatform(-2.0f, -3.0f, 0.1f, 0.6f);
}

void Render::DrawTest()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(VAO);

	viewMatrix = glm::mat4();
	projectionMatrix = glm::mat4();

	//view = glm::lookAt();
	projectionMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f);

	// Draw models
	shaderModel.Use();

	modelLoc = glGetUniformLocation(shaderModel.shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderModel.shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderModel.shaderProgram, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	for (unsigned int i = 0; i < modelsVector.size(); ++i)
	{
		modelMatrix = glm::mat4();

		modelMatrix = glm::translate(modelMatrix, glm::vec3(modelsVector[i].GetXPos(), modelsVector[i].GetYPos(), -10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	// Draw platforms
	shaderPlatform.Use();

	modelLoc = glGetUniformLocation(shaderPlatform.shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderPlatform.shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderPlatform.shaderProgram, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	for (unsigned int i = 0; i < platformsVector.size(); ++i)
	{
		modelMatrix = glm::mat4();

		modelMatrix = glm::translate(modelMatrix, glm::vec3(platformsVector[i].GetXPos(), platformsVector[i].GetYPos(), -10.0f)) * glm::scale(modelMatrix, glm::vec3(platformsVector[i].GetWidth(), platformsVector[i].GetHeight(), 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}

void Render::AddPlatform(const float& _xPos, const float& _yPos, const float& _width, const float& _height)
{
	Platform addPlatform;
	
	addPlatform.SetXPos(_xPos);
	addPlatform.SetYPos(_yPos);
	addPlatform.SetWidth(_width);
	addPlatform.SetHeight(_height);

	platformsVector.push_back(addPlatform);
}

void Render::AddModel(const float& _xPos, const float& _yPos)
{
	Model addModel;

	addModel.SetXPos(_xPos);
	addModel.SetYPos(_yPos);

	modelsVector.push_back(addModel);
}