#include "Camera.h"

Camera* Camera::camera;
glm::vec3 Camera::centerVec = glm::vec3(0.0f, 0.0f, 2.0f);
glm::vec3 Camera::eyeVec = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Camera::upVec = glm::vec3(0.0f, 1.0f, 0.0f);

Camera* Camera::GetCamera()
{
	if (camera == 0)
		camera = new Camera();
	return camera;
}

void Camera::UpdateCameraVectors(const float& _xPos, const float& _yPos)
{	
	float xPos = _xPos - (MainWindow::GetWindowWidth() - 32.0f) / 2.0f;

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


