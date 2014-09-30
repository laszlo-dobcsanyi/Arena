#ifndef PLATFORM_H
#define PLATFORM_H

//GLFW
#include <GLFW/glfw3.h>

class Platform
{
public:
	Platform();

	GLfloat vertices[8];
	GLuint indices[6];

	float& GetXPos() { return xPos; }
	float& GetYPos() { return yPos; }
	float& GetWidth() { return width; }
	float& GetHeight() { return height; }

	void SetXPos(const float& _xPos) { xPos = _xPos; }
	void SetYPos(const float& _yPos) { yPos = _yPos; }
	void SetWidth(const float& _width) { width = _width; }
	void SetHeight(const float& _height) { height = _height; }

private:
	void Load();
	void LoadVertices();
	void LoadTexture();

	float xPos;
	float yPos;
	float width;
	float height;
};

#endif // PLATFORM_H