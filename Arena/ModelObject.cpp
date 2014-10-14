#include "ModelObject.h"

ModelObject::ModelObject() {}

void ModelObject::LoadTexture(const GLchar* _texturePath)
{
	texture = new Texture(_texturePath);
}