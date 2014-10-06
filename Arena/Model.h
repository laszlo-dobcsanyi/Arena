#ifndef MODEL_H
#define MODEL_H

//GLFW
#include <GLFW/glfw3.h>

class Model
{
public:
	Model();

	float& GetXPos() { return xPos; }
	float& GetYPos() { return yPos; }

	void SetXPos(const float& _xPos) { xPos = _xPos; }
	void SetYPos(const float& _yPos) { yPos = _yPos; }

private:
	void Load();
	void LoadVertices();
	void LoadTexture();

	float xPos;
	float yPos;
};

#endif // MODEL_H