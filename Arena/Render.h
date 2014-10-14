#ifndef RENDER_H
#define RENDER_H

#include <forward_list>

#include <boost\shared_ptr.hpp>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define CAMERA_ASPECT_RATIO				16.0f/9.0f
#define CAMERA_VIEW_MIN_DISTANCE		-100.0f
#define CAMERA_VIEW_MAX_DISTANCE		1000.0f

class Camera;
class Shader;
class Game;
class Object;

struct ModelShape
{
	GLfloat vertices[28];
	GLuint indices[6];
};

class Render
{
public:
	Render();

	void Draw();
	void InitModelShape(const boost::shared_ptr< Object > _modelObject);
	void AddHero(const float& _xPos, const float& _yPos);
	void AddWall(const float& _xPos, const float& _yPos, const float& width, const float& height);

	GLuint& GetVAO() { return VAO; }
	GLuint& GetVBO() { return VBO; }
	GLuint& GetEBO() { return EBO; }

private:
	void DrawBackground();
	void DrawHeroes();
	void DrawWalls();
	// TODO: void DrawProjectiles();

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	Game* game;
	Shader* shaderModel;
	Shader* shaderPlatform;
	Camera* camera;
	ModelShape modelShape;
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	GLint modelLoc;
	GLint viewLoc;
	GLint projLoc;
};

#endif // RENDER_H