#include "Render.h"

Render::Render() :	TestShaderModel("Shaders\\Model.vs", "Shaders\\Model.frag"),
					TestShaderPlatform("Shaders\\Platform.vs", "Shaders\\Platform.frag"),
					TestModel()
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

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TestModel.vertices), TestModel.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(TestModel.indices), TestModel.indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	AddPlatform(-1.0f, 0.0f, 0.5f, 0.5f);
	AddPlatform(-2.0f, -3.0f, 0.1f, 0.6f);
}

void Render::DrawTest()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	TestShaderModel.Use();

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	view = glm::translate(view, glm::vec3(0.5f, 0.5f, -10.0f));
	projection = glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f);

	GLint modelLoc = glGetUniformLocation(TestShaderModel.ShaderProgram, "model");
	GLint viewLoc = glGetUniformLocation(TestShaderModel.ShaderProgram, "view");
	GLint projLoc = glGetUniformLocation(TestShaderModel.ShaderProgram, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	TestShaderPlatform.Use();

	for (unsigned int i = 0; i < TestPlatforms.size(); ++i)
	{
		model = glm::mat4();
		view = glm::mat4();
		projection = glm::mat4();
		model = glm::scale(model, glm::vec3(TestPlatforms[i].GetWidth(), TestPlatforms[i].GetHeight(), 1.0f));
		view = glm::translate(view, glm::vec3(TestPlatforms[i].GetXPos(), TestPlatforms[i].GetYPos(), -10.0f));
		projection = glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f);

		GLint modelLoc = glGetUniformLocation(TestShaderModel.ShaderProgram, "model");
		GLint viewLoc = glGetUniformLocation(TestShaderModel.ShaderProgram, "view");
		GLint projLoc = glGetUniformLocation(TestShaderModel.ShaderProgram, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void Render::AddPlatform(const float& _xPos, const float& _yPos, const float& _width, const float& _height)
{
	Platform platform;
	
	platform.SetXPos(_xPos);
	platform.SetYPos(_yPos);
	platform.SetWidth(_width);
	platform.SetHeight(_height);

	TestPlatforms.push_back(platform);
}