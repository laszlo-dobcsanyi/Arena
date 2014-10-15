#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "MainWindow.h"

#define WINDOW_CAMERA_BOTTOM_LIMIT		(MainWindow::GetWindowHeight() - 32.0f) / 2.0f

class Camera
{
public:
	static void UpdateCameraVectors(const float& _xPos, const float& _yPos);

	static Camera* GetCamera();
	static glm::vec3& GetCenterVec() { return centerVec; }
	static glm::vec3& GetEyeVec() { return eyeVec; }
	static glm::vec3& GetUpVec() { return upVec; }

private:
	Camera() {}

	Camera(Camera const&);
	void operator=(Camera const&);

	static Camera* camera;
	static glm::vec3 centerVec;
	static glm::vec3 eyeVec;
	static glm::vec3 upVec;
};

#endif // CAMERA_H