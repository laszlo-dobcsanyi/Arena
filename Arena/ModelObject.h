#ifndef MODELOBJECT_H
#define MODELOBJECT_H

#define HERO_WIDTH			32.0f
#define HERO_HEIGHT			32.0f

class ModelObject
{
public:
	ModelObject();

	float& GetXPos() { return xPos; }
	float& GetYPos() { return yPos; }
	float& GetWidth() { return width; }
	float& GetHeight() { return height; }

	void SetXPos(const float& _xPos) { xPos = _xPos; }
	void SetYPos(const float& _yPos) { yPos = _yPos; }
	void SetWidth(const float& _width) { width = _width; }
	void SetHeight(const float& _height) { height = _height; }

private:
	void LoadTexture();

	float xPos;
	float yPos;
	float width;
	float height;
};

#endif // MODELOBJECT_H