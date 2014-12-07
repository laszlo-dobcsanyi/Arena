#ifndef GAME_WALL_H
#define GAME_WALL_H

//#include <forward_list>

#include <boost\shared_ptr.hpp>

#include "Game\Descriptor.h"
#include "Game\Object.hpp"
#include "Game\Collision.h"
#include "Graphics\Shader.h"
#include "Graphics\Representation.h"

class Hero;
class Texture;

struct Wall_Descriptor : public Descriptor
{
public:
	Wall_Descriptor(const Vector2 &_p1, const Vector2 &_p2);
	Wall_Descriptor(const Vector2& _center, const float& _width, const float& _height);
	Wall_Descriptor(const float &_x1, const float &_y1, const float &_x2, const float &_y2);
	Wall_Descriptor(const Wall_Descriptor &_other);
	Wall_Descriptor & operator=(const Wall_Descriptor &_other);
	~Wall_Descriptor();

	void Represent(char * _segment);
};

class Wall_Representation : public Representation< Wall_Descriptor >
{
public:
	void Draw(const Wall_Descriptor &_descriptor);

protected:
	Texture *texture = 0;

	Wall_Representation(const char* _texture_path);
	~Wall_Representation();

private:
	Wall_Representation(const Wall_Representation &_other);
	Wall_Representation operator=(const Wall_Representation &_other);
};

class Wall : public Object_Static< Wall_Descriptor >, public Wall_Representation
{
public:
	Wall(const Wall_Descriptor& _state, const char* _texture_path);
	~Wall();

	void Collision_Hero(boost::shared_ptr< Hero > _hero, const Collision_Type::Type& _type);

private:
	Wall(const Wall& _other);
	Wall& operator=(const Wall& _other);
};
#endif