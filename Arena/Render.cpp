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
	//TODO: LoadMainModelShape();

	glBindVertexArray(VAO);

	GLfloat vertices[] = {
		 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	AddHero(500.0f, 500.0f);
	AddWall(0.0f, 0.0f, 1280.0f, 100.0f);
}

void Render::Draw()
{
	glBindVertexArray(VAO);

	DrawBackground();

	projectionMatrix = glm::mat4();

	//TEST ON
	boost::shared_ptr<ModelObject> firstHero = heroes.front();
	camera.UpdateCameraVectors(firstHero->GetXPos(), firstHero->GetYPos());
	//TEST OFF
	
	viewMatrix = glm::lookAt(camera.GetCenterVec(), camera.GetEyeVec(), camera.GetUpVec());
	projectionMatrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, CAMERA_VIEW_MIN_DISTANCE, CAMERA_VIEW_MAX_DISTANCE); // TODO: Get MainWindow width and height! Move this matrix to init function!

	DrawWalls();
	DrawHeroes();

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
		glBindTexture(GL_TEXTURE_2D, hero->GetTextureID());

		modelMatrix = glm::mat4();

		// TEST ON
		hero->SetYPos(hero->GetYPos() - 1);
		// TEST OFF

		modelMatrix = glm::translate(modelMatrix, glm::vec3(hero->GetXPos(), hero->GetYPos(), -10.0f)) * glm::scale(modelMatrix, glm::vec3(hero->GetWidth(), hero->GetHeight(), 1.0f));
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
		glBindTexture(GL_TEXTURE_2D, wall->GetTextureID());
		modelMatrix = glm::mat4();

		modelMatrix = glm::translate(modelMatrix, glm::vec3(wall->GetXPos(), wall->GetYPos(), -19.0f)) * glm::scale(modelMatrix, glm::vec3(wall->GetWidth(), wall->GetHeight(), 1.0f));
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
	addHero->LoadTexture("Textures\\awesomeface.png");

	heroes.push_front(addHero);
}

void Render::AddWall(const float& _xPos, const float& _yPos, const float& _width, const float& _height)
{
	boost::shared_ptr<ModelObject> addWall(new ModelObject);
	
	addWall->SetXPos(_xPos);
	addWall->SetYPos(_yPos);
	addWall->SetWidth(_width);
	addWall->SetHeight(_height);
	addWall->LoadTexture("Textures\\wall.png");

	walls.push_front(addWall);
}