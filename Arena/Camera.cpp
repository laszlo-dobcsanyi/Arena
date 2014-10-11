#include "Camera.h"

#include <iostream>
Camera::Camera()
{
	centerVec = glm::vec3(0.0f, 0.0f, 2.0f);
	eyeVec = glm::vec3(0.0f, 0.0f, 0.0f);
	upVec = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::UpdateCameraVectors(const float& _xPos, const float& _yPos)
{	
	float xPos = _xPos - (MainWindow::GetWindowWidth() - HERO_WIDTH) / 2.0f;

	if (_yPos < WINDOW_CAMERA_BOTTOM_LIMIT)
	{

		centerVec = glm::vec3(xPos, 0.0f, 1.0f);
		eyeVec = glm::vec3(xPos, 0.0f, 0.0f);
	}
	else
	{
		float yPos = _yPos - WINDOW_CAMERA_BOTTOM_LIMIT;

		centerVec = glm::vec3(xPos, yPos, 1.0f);
		eyeVec = glm::vec3(xPos, yPos, 0.0f);
	}
}


