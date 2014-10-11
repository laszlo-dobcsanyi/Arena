#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define WINDOW_CAMERA_BOTTOM_LIMIT		328.0f // TODO: NOT CONST!

class Camera
{
public:
	Camera();

	void UpdateCameraVectors(const float& _xPos, const float& _yPos);

	glm::vec3& GetCenterVec() { return centerVec; }
	glm::vec3& GetEyeVec() { return eyeVec; }
	glm::vec3& GetUpVec() { return upVec; }

private:
	glm::vec3 centerVec;
	glm::vec3 eyeVec;
	glm::vec3 upVec;
};

#endif // CAMERA_H