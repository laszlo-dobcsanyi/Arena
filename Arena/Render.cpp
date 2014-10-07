#include <boost/foreach.hpp>

#include "Render.h"
#include "ModelObject.h"

Render::Render() :	shaderModel("Shaders\\Model.vs", "Shaders\\Model.frag"),
					shaderPlatform("Shaders\\Platform.vs", "Shaders\\Platform.frag"),
					modelMainShape()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Render::InitRender()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(modelMainShape.vertices), modelMainShape.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(modelMainShape.indices), modelMainShape.indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	AddHero(1.0f, 1.0f);
	AddWall(0.0f, 2.0f, 3.0f, 0.5f);
	AddWall(-2.0f, -3.0f, 0.1f, 0.6f);
}

void Render::Draw()
{
	DrawBackground();

	glBindVertexArray(VAO);

	viewMatrix = glm::mat4();
	projectionMatrix = glm::mat4();

	//view = glm::lookAt();
	projectionMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 1000.0f);

	DrawHeroes();
	DrawWalls();

	glBindVertexArray(0);
	
	// TODO: DrawProjectiles();
}

void Render::DrawBackground()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::DrawHeroes()
{
	shaderModel.Use();

	modelLoc = glGetUniformLocation(shaderModel.shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderModel.shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderModel.shaderProgram, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	BOOST_FOREACH(boost::shared_ptr < ModelObject > hero, heroes)
	{
		modelMatrix = glm::mat4();

		modelMatrix = glm::translate(modelMatrix, glm::vec3(hero->GetXPos(), hero->GetYPos(), -10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void Render::DrawWalls()
{
	shaderPlatform.Use();

	modelLoc = glGetUniformLocation(shaderPlatform.shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderPlatform.shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderPlatform.shaderProgram, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	BOOST_FOREACH(boost::shared_ptr < ModelObject > wall, walls)
	{
		modelMatrix = glm::mat4();

		modelMatrix = glm::translate(modelMatrix, glm::vec3(wall->GetXPos(), wall->GetYPos(), -10.0f)) * glm::scale(modelMatrix, glm::vec3(wall->GetWidth(), wall->GetHeight(), 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void Render::AddHero(const float& _xPos, const float& _yPos)
{
	boost::shared_ptr<ModelObject> addHero(new ModelObject);

	addHero->SetXPos(_xPos);
	addHero->SetYPos(_yPos);
	addHero->SetWidth(HERO_WIDTH);
	addHero->SetHeight(HERO_HEIGHT);

	heroes.push_front(addHero);
}

void Render::AddWall(const float& _xPos, const float& _yPos, const float& _width, const float& _height)
{
	boost::shared_ptr<ModelObject> addWall(new ModelObject);
	
	addWall->SetXPos(_xPos);
	addWall->SetYPos(_yPos);
	addWall->SetWidth(_width);
	addWall->SetHeight(_height);

	walls.push_front(addWall);
}