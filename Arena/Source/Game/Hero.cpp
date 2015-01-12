#include <iostream>

#include "Macro"
#include "Core\Configuration.h"
#include "Game\Hero.h"
#include "Game\Wall.h"
#include "Graphics\Graphics.h"
#include "Graphics\Shader.h"
#include "Graphics\Texture.h"

/// Descriptors
/*Hero_Network_Descriptor::Hero_Network_Descriptor() :
	Descriptor(Vector2(0.f, 0.f), 32.f, 32.f)
{

}*/

Hero_Descriptor::Hero_Descriptor() :
	Descriptor_Dynamic(Vector2(0.f, 0.f), 32.f, 32.f)
{

}

Hero_Descriptor::Hero_Descriptor(const Vector2& _center) :
	Descriptor_Dynamic(_center, 32.f, 32.f)
{

}

/*Hero_Descriptor::Hero_Descriptor(const Hero_Descriptor &_other) :
	Descriptor(_other)
{

}

Hero_Descriptor & Hero_Descriptor::operator=(const Hero_Descriptor &_other)
{
	Descriptor::operator=(_other);

	movement = _other.movement;

	velocity = _other.velocity;
	force = _other.force;

	base = _other.base;
	base_type = _other.base_type;

	return *this;
}



Hero_Descriptor::~Hero_Descriptor()
{

}*/

/// Representation
Hero_Representation::Hero_Representation(const char* _texture_path) :
	Representation()
{
	texture = new Texture(_texture_path);
}

void Hero_Representation::Draw(const Hero_Descriptor &_descriptor)
{
	glBindTexture(GL_TEXTURE_2D, texture->textureID);

	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(_descriptor.center.x, _descriptor.center.y, -10.0f));
	GLint modelLoc = glGetUniformLocation(Graphics::shader_hero->shaderProgram, "model");
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

Hero_Representation::~Hero_Representation()
{

}

/// Object
Hero::Hero(const Hero_Descriptor &_state, const char* _texture_path) :
	Object_Dynamic< Hero_Descriptor >(Configuration::hero_state_buffer_size, _state), 
	Hero_Representation(_texture_path)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::hero, "\t+> Creating Hero..");
	Logger::counter_heroes++;
	#endif

	Move(0);
}

///

void Hero::Update(const float& _elapsed_time)
{
	Hero_Descriptor *current = states.Current();
	Hero_Descriptor *next = states.Next();

	if (current->base_type != Collision_Type::NONE)
	{
		if (!(current->movement & Hero_Movement::RIGHT) && 0.f < current->velocity.x) next->velocity.x = current->velocity.x < 1.f ? 0.f : current->velocity.x * 0.95f;
		if (!(current->movement & Hero_Movement::LEFT) && current->velocity.x < 0.f) next->velocity.x = -1.f < current->velocity.x ? 0.f : current->velocity.x * 0.95f;
	}

	const float max_speed = 64.f;
	if (max_speed < abs(next->velocity.x)) next->velocity.x = next->velocity.x < 0.f ? -max_speed : max_speed;
	if (max_speed < abs(next->velocity.y)) next->velocity.y = next->velocity.y < 0.f ? -max_speed : max_speed;

	next->velocity = current->velocity + (next->force * _elapsed_time);
	next->center = current->center + next->velocity;
}

void Hero::Move(const uint8_t &_state)
{
	Hero_Descriptor *current = states.Current();
	Hero_Descriptor *next = states.Next();

	const float speed = 16.f;
	switch (current->base_type)
	{
		case Collision_Type::NONE:
		next->force = Vector2(0., -speed);
		if (!(current->movement & Hero_Movement::RIGHT) && _state & Hero_Movement::RIGHT)	{ next->force.x += +speed; current->movement |= Hero_Movement::RIGHT; }
		if (!(current->movement & Hero_Movement::LEFT) && _state & Hero_Movement::LEFT)		{ next->force.x += -speed; current->movement |= Hero_Movement::LEFT; }
		break;

		case Collision_Type::RIGHT:
		next->force = Vector2(0., -speed);
		if (!(current->movement & Hero_Movement::UP) && _state & Hero_Movement::UP)			{ next->force.y += +speed / 2.f; current->movement |= Hero_Movement::UP; }
		if (!(current->movement & Hero_Movement::DOWN) && _state & Hero_Movement::DOWN)		{ next->force.y += -speed / 2.f; current->movement |= Hero_Movement::DOWN; }
		if (!(current->movement & Hero_Movement::JUMP) && _state & Hero_Movement::JUMP)		{ if (current->velocity.y <= 0.f) { next->force = next->force + Vector2(+speed * 24, +speed * 32); current->movement |= Hero_Movement::JUMP; } }
		break;

		case Collision_Type::TOP:
		next->force = Vector2(0., 0.);
		if (!(current->movement & Hero_Movement::RIGHT) && _state & Hero_Movement::RIGHT)	{ next->force.x += +speed; current->movement |= Hero_Movement::RIGHT; }
		if (!(current->movement & Hero_Movement::LEFT) && _state & Hero_Movement::LEFT)		{ next->force.x += -speed; current->movement |= Hero_Movement::LEFT; }
		if (!(current->movement & Hero_Movement::JUMP) && _state & Hero_Movement::JUMP)		{ if (current->velocity.y <= 0.f) { next->force.y += +speed * 32; current->movement |= Hero_Movement::JUMP; } }
		break;

		case Collision_Type::LEFT:
		next->force = Vector2(0., -speed);
		if (!(current->movement & Hero_Movement::UP) && _state & Hero_Movement::UP)			{ next->force.y += +speed / 2.f; current->movement |= Hero_Movement::UP; }
		if (!(current->movement & Hero_Movement::DOWN) && _state & Hero_Movement::DOWN)		{ next->force.y += -speed / 2.f; current->movement |= Hero_Movement::DOWN; }
		if (!(current->movement & Hero_Movement::JUMP) && _state & Hero_Movement::JUMP)		{ if (current->velocity.y <= 0.f) { next->force = next->force + Vector2(-speed * 24, +speed * 32); current->movement |= Hero_Movement::JUMP; } }
		break;

		case Collision_Type::BOTTOM:
		next->force = Vector2(0., -speed);
		break;
	}

	if (current->movement & Hero_Movement::UP && !(_state & Hero_Movement::UP))			{ current->movement &= ~Hero_Movement::UP; }
	if (current->movement & Hero_Movement::DOWN && !(_state & Hero_Movement::DOWN))		{ current->movement &= ~Hero_Movement::DOWN; }
	if (current->movement & Hero_Movement::RIGHT && !(_state & Hero_Movement::RIGHT))	{ current->movement &= ~Hero_Movement::RIGHT; }
	if (current->movement & Hero_Movement::LEFT && !(_state & Hero_Movement::LEFT))		{ current->movement &= ~Hero_Movement::LEFT; }
	if (current->movement & Hero_Movement::JUMP && !(_state & Hero_Movement::JUMP))		{ current->movement &= ~Hero_Movement::JUMP; }
}

///

void Hero::Collision_Hero(boost::shared_ptr< Hero > _other, const Collision_Type::Type& _type)
{

}

void Hero::Collision_Wall(boost::shared_ptr< Wall > _wall, const Collision_Type::Type& _type)
{
	Hero_Descriptor *next = states.Next();

	if (next->base)
	{
		if (_type < next->base_type)
		{
			next->base = _wall;
			next->base_type = _type;
		}
	}
	else
	{
		if (next->base_type != Collision_Type::BOTTOM)
		{
			next->base = _wall;
			next->base_type = _type;
		}
	}

	//std::cout << "Hero COLLISION: " << _type << " : C [" << updated_center.x << ":" << updated_center.y << "] V [" << velocity.x << ":" << velocity.y << "]" << std::endl;
}

void Hero::Dispose()
{
	if (disposed) return; disposed = true;

	#ifdef LOGGING
	Logger::Write(LogMask::dispose, LogObject::hero, "\t<- Disposing Hero..");
	#endif
}

Hero::~Hero()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::hero, "\t-> Destroying Hero..");
	#endif

	//base = 0;
	// TODO should be dispose, right?!
	delete texture;

	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::hero, "\t<- Hero Destroyed!");
	Logger::counter_heroes--;
	#endif
}
