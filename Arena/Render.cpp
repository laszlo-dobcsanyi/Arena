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
	DrawObjects();
	DrawModells();
	DrawProjectiles();
}

void Render::DrawBackground()
{

}

void Render::DrawObjects()
{

}

void Render::DrawModells()
{

}

void Render::DrawProjectiles()
{

}
