#ifndef MODEL_H
#define MODEL_H

//GLFW
#include <GLFW/glfw3.h>

class Model
{
public:
	Model();

	GLfloat vertices[8];
	GLuint indices[6];
private:
	void Load();
	void LoadVertices();
	void LoadTexture();
};

#endif // MODEL_H