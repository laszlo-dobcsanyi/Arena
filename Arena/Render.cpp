#include <boost/foreach.hpp>

#include "Render.h"
#include "ModelObject.h"
#include "MainWindow.h"
#include "Shader.h"
#include "Camera.h"

Render::Render() :	shaderModel(new Shader("Shaders\\Model.vs", "Shaders\\Model.frag")),
					shaderPlatform(new Shader("Shaders\\Platform.vs", "Shaders\\Platform.frag")),
					camera(new Camera)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	projectionMatrix = glm::mat4();
	projectionMatrix = glm::ortho(0.0f, (float)MainWindow::GetWindowWidth(), 0.0f, (float)MainWindow::GetWindowHeight(), CAMERA_VIEW_MIN_DISTANCE, CAMERA_VIEW_MAX_DISTANCE);

	AddHero(500.0f, 500.0f);
	AddWall(0.0f, 0.0f, 1280.0f, 100.0f);
}

void Render::Draw()
{
	glBindVertexArray(VAO);

	DrawBackground();

	// TEST ON
	boost::shared_ptr<ModelObject> firstHero = heroes.front();
	camera->UpdateCameraVectors(firstHero->GetXPos(), firstHero->GetYPos());
	// TEST OFF
	
	viewMatrix = glm::lookAt(camera->GetCenterVec(), camera->GetEyeVec(), camera->GetUpVec());

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

void Render::DrawWalls()
{
	shaderPlatform->Use();

	modelLoc = glGetUniformLocation(shaderPlatform->shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderPlatform->shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderPlatform->shaderProgram, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	BOOST_FOREACH(boost::shared_ptr < ModelObject > wall, walls)
	{
		glBindTexture(GL_TEXTURE_2D, wall->GetTextureID());
		modelMatrix = glm::mat4();

		modelMatrix = glm::translate(modelMatrix, glm::vec3(wall->GetXPos(), wall->GetYPos(), -10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		InitModelShape(wall);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void Render::DrawHeroes()
{
	shaderModel->Use();

	modelLoc = glGetUniformLocation(shaderModel->shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderModel->shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderModel->shaderProgram, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	BOOST_FOREACH(boost::shared_ptr < ModelObject > hero, heroes)
	{
		glBindTexture(GL_TEXTURE_2D, hero->GetTextureID());

		modelMatrix = glm::mat4();

		// TEST ON
		hero->SetYPos(hero->GetYPos() - 1);
		// TEST OFF

		modelMatrix = glm::translate(modelMatrix, glm::vec3(hero->GetXPos(), hero->GetYPos(), -10.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		InitModelShape(hero);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void Render::InitModelShape(const boost::shared_ptr< ModelObject > _modelObject)
{
	float shapeWidth = (float)(_modelObject->GetWidth());
	float shapeHeight = (float)(_modelObject->GetHeight());
	float textureWidthRatio = (float)(shapeWidth * 2 / _modelObject->GetTextureWidth());
	float textureHeightRatio = (float)(shapeHeight * 2 / _modelObject->GetTextureHeight());

	// TOP RIGHT:
	// Position Coords:
	modelShape.vertices[ 0] =  shapeWidth;
	modelShape.vertices[ 1] =  shapeHeight;

	// Colors:
	modelShape.vertices[ 2] =  1.0f;
	modelShape.vertices[ 3] =  0.0f;
	modelShape.vertices[ 4] =  0.0f;

	// Texture Coords:
	modelShape.vertices[ 5] =  textureWidthRatio;
	modelShape.vertices[ 6] =  textureHeightRatio;
	// ----------------------------

	// BOTTOM RIGHT:
	// Position Coords:
	modelShape.vertices[ 7] =  shapeWidth;
	modelShape.vertices[ 8] = -shapeHeight;

	// Colors:
	modelShape.vertices[ 9] =  0.0f;
	modelShape.vertices[10] =  1.0f;
	modelShape.vertices[11] =  0.0f;

	// Texture Coords:
	modelShape.vertices[12] =  textureWidthRatio;
	modelShape.vertices[13] =  0.0f;
	// ----------------------------

	// BOTTOM LEFT:
	// Position Coords:
	modelShape.vertices[14] = -shapeWidth;
	modelShape.vertices[15] = -shapeHeight;

	// Colors:
	modelShape.vertices[16] =  0.0f;
	modelShape.vertices[17] =  0.0f;
	modelShape.vertices[18] =  1.0f;

	// Texture Coords:
	modelShape.vertices[19] =  0.0f;
	modelShape.vertices[20] =  0.0f;
	// ----------------------------

	// TOP LEFT:
	// Position Coords:
	modelShape.vertices[21] = -shapeWidth;
	modelShape.vertices[22] =  shapeHeight;

	// Colors:
	modelShape.vertices[23] =  1.0f;
	modelShape.vertices[24] =  1.0f;
	modelShape.vertices[25] =  0.0f;

	// Texture Coords:
	modelShape.vertices[26] =  0.0f;
	modelShape.vertices[27] =  textureHeightRatio;
	// ----------------------------

	modelShape.indices[0] = 0;
	modelShape.indices[1] = 1;
	modelShape.indices[2] = 3;
	modelShape.indices[3] = 1;
	modelShape.indices[4] = 2;
	modelShape.indices[5] = 3;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(modelShape.vertices), modelShape.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(modelShape.indices), modelShape.indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
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