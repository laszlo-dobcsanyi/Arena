#include "Camera.h"

#include <iostream>
Camera::Camera()
{
	centerVec = glm::vec3(0.0f, 0.0f, 2.0f);
	eyeVec = glm::vec3(0.0f, 0.0f, 0.0f);
	upVec = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::UpdateCameraVectors(const float& _xPos, const float& _yPos) // TODO: Get MainWindow width and height!
{	
	float xPos = _xPos - (1280.0f - 64.0f) / 2.0f;

	if (_yPos < WINDOW_CAMERA_BOTTOM_LIMIT)
	{

		centerVec = glm::vec3(xPos, 0.0f, 1.0f);
		eyeVec = glm::vec3(xPos, 0.0f, 0.0f);

		std::cout << "FINITO!\n";
	}
	else
	{
		float yPos = _yPos - (720.0f - 64.0f) / 2.0f;

		centerVec = glm::vec3(xPos, yPos, 1.0f);
		eyeVec = glm::vec3(xPos, yPos, 0.0f);

		std::cout << "X position: " << xPos << '\n';
		std::cout << "Y position: " << yPos << '\n';
		std::cout << "-----------\n";
	}
}


