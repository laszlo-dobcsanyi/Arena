#include "Platform.h"

Platform::Platform()
{
	Load();
}

void Platform::Load()
{
	LoadVertices();
	LoadTexture();
}

void Platform::LoadVertices()
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

void Platform::LoadTexture()
{

}