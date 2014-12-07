
#include <iostream>

#include "Macro"
#include "Game\Wall.h"
#include "Game\Hero.h"
#include "Graphics\Graphics.h"
#include "Graphics\Texture.h"

/// Descriptor
Wall_Descriptor::Wall_Descriptor(const Vector2 &_p1, const Vector2 &_p2) :
	Wall_Descriptor(_p1.x, _p1.y, _p2.x, _p2.y)
{

}

Wall_Descriptor::Wall_Descriptor(const float &_x1, const float &_y1, const float &_x2, const float &_y2) :
	Wall_Descriptor(Vector2((_x1 + _x2) / 2.f, (_y1 + _y2) / 2.f), (_x2 - _x1) / 2.f, (_y1 - _y2) / 2.f)
{

}


Wall_Descriptor::Wall_Descriptor(const Vector2& _center, const float& _width, const float& _height) :
	Descriptor(_center, _width, _height)
{

}

/*Wall_Descriptor::Wall_Descriptor(const Wall_Descriptor &_other) :
	Descriptor(_other)
{

}

Wall_Descriptor & Wall_Descriptor::operator=(const Wall_Descriptor &_other)
{
	Descriptor::operator=(_other);
	return *this;
}*/

void Wall_Descriptor::Describe(char * _segment)
{
	memcpy(_segment, this, sizeof(this));
}

/*Wall_Descriptor::~Wall_Descriptor()
{

}*/


/// Representation
Wall_Representation::Wall_Representation(const char* _texture_path)
{
	texture = new Texture(_texture_path);
}

void Wall_Representation::Draw(const Wall_Descriptor &_descriptor)
{
	glBindTexture(GL_TEXTURE_2D, texture->textureID);

	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(_descriptor.center.x, _descriptor.center.y, -10.0f));
	GLint modelLoc = glGetUniformLocation(Graphics::shader_wall->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	float shapeWidth = (float)(_descriptor.width);
	float shapeHeight = (float)(_descriptor.height);
	float textureWidthRatio = (float)(shapeWidth * 2 / texture->width);
	float textureHeightRatio = (float)(shapeHeight * 2 / texture->height);

	struct ModelShape
	{
	public:
		GLfloat vertices[28];
		GLuint indices[6];
	} modelShape;

	// TOP RIGHT:
	// Position Coords:
	modelShape.vertices[0] = shapeWidth;
	modelShape.vertices[1] = shapeHeight;

	// Colors:
	modelShape.vertices[2] = 1.0f;
	modelShape.vertices[3] = 0.0f;
	modelShape.vertices[4] = 0.0f;

	// Texture Coords:
	modelShape.vertices[5] = textureWidthRatio;
	modelShape.vertices[6] = textureHeightRatio;
	// ----------------------------

	// BOTTOM RIGHT:
	// Position Coords:
	modelShape.vertices[7] = shapeWidth;
	modelShape.vertices[8] = -shapeHeight;

	// Colors:
	modelShape.vertices[9] = 0.0f;
	modelShape.vertices[10] = 1.0f;
	modelShape.vertices[11] = 0.0f;

	// Texture Coords:
	modelShape.vertices[12] = textureWidthRatio;
	modelShape.vertices[13] = 0.0f;
	// ----------------------------

	// BOTTOM LEFT:
	// Position Coords:
	modelShape.vertices[14] = -shapeWidth;
	modelShape.vertices[15] = -shapeHeight;

	// Colors:
	modelShape.vertices[16] = 0.0f;
	modelShape.vertices[17] = 0.0f;
	modelShape.vertices[18] = 1.0f;

	// Texture Coords:
	modelShape.vertices[19] = 0.0f;
	modelShape.vertices[20] = 0.0f;
	// ----------------------------

	// TOP LEFT:
	// Position Coords:
	modelShape.vertices[21] = -shapeWidth;
	modelShape.vertices[22] = shapeHeight;

	// Colors:
	modelShape.vertices[23] = 1.0f;
	modelShape.vertices[24] = 1.0f;
	modelShape.vertices[25] = 0.0f;

	// Texture Coords:
	modelShape.vertices[26] = 0.0f;
	modelShape.vertices[27] = textureHeightRatio;
	// ----------------------------

	modelShape.indices[0] = 0;
	modelShape.indices[1] = 1;
	modelShape.indices[2] = 3;
	modelShape.indices[3] = 1;
	modelShape.indices[4] = 2;
	modelShape.indices[5] = 3;

	glBindBuffer(GL_ARRAY_BUFFER, Graphics::VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(modelShape.vertices), modelShape.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Graphics::EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(modelShape.indices), modelShape.indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Wall_Representation::~Wall_Representation()
{

}

/// Object
Wall::Wall(const Wall_Descriptor &_state, const char* _texture_path) :
	Object_Static(_state),
	Wall_Representation(_texture_path)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::wall, "\t+> Wall Created!");
	Logger::counter_walls++;
	#endif
}

void Wall::Collision_Hero(boost::shared_ptr< Hero > _hero, const Collision_Type::Type& _type)
{
	Hero_Descriptor *hero_next = _hero->states.Next();
	switch (_type)
	{
		case Collision_Type::RIGHT:		hero_next->center.x = center.x + width + hero_next->width;		hero_next->velocity.x = 0.;	break;
		case Collision_Type::TOP:		hero_next->center.y = center.y + height + hero_next->height;	hero_next->velocity.y = 0.; break;
		case Collision_Type::LEFT:		hero_next->center.x = center.x - width - hero_next->width;		hero_next->velocity.x = 0.;	break;
		case Collision_Type::BOTTOM:	hero_next->center.y = center.y - height - hero_next->height;	hero_next->velocity.y = 0.; break;
		default:
			#ifdef LOGGING
			Logger::Write(LogMask::error, LogObject::wall, "# Collision failed!");
			#endif
			break;
	}
}

Wall::~Wall()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::wall, "\t<- Wall Destroyed!");
	Logger::counter_walls--;
	#endif
}
