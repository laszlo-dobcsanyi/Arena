#ifndef GRAPHICS_RENDER_H
#define GRAPHICS_RENDER_H

#include <string>
#include <forward_list>

#include <boost\shared_ptr.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

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
	void InitGameRender();

	void Draw();
	void InitModelShape(const boost::shared_ptr< Object > _modelObject);

	GLuint& GetVAO() { return VAO; }
	GLuint& GetVBO() { return VBO; }
	GLuint& GetEBO() { return EBO; }

private:
	void DrawBackground();
	void DrawHeroes();
	void DrawWalls();

	void DrawString(FT_Face *_face, const std::string &_text, float _x, float _y, const float &_sx, const float &_sy);

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	FT_Library font_library;
	FT_Face face_outwrite;

	Game* game;
	Shader* shaderWall;
	Shader* shaderHero;
	Shader *shaderText;
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