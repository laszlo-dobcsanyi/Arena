#include "Render.h"

Render::Render()
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
