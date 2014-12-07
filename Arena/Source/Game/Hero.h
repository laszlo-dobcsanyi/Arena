#ifndef GAME_HERO_H
#define GAME_HERO_H

#include <cstdint>

#include <boost\atomic.hpp>
#include <boost\shared_ptr.hpp>

#include "Game\Descriptor.h"
#include "Game\Object.hpp"
#include "Game\Collision.h"
#include "Graphics\Shader.h"
#include "Graphics\Representation.h"

class Wall;
class Texture;

namespace Hero_Movement
{
	enum Type
	{
		RIGHT	= 1 << 1,
		UP		= 1 << 2,
		LEFT	= 1 << 3,
		DOWN	= 1 << 4,
		JUMP	= 1 << 5
	};
};


struct Hero_Descriptor : public Descriptor
{
public:
	Hero_Descriptor();
	Hero_Descriptor(const Vector2& _center);
	Hero_Descriptor(const Hero_Descriptor &_other);
	Hero_Descriptor & operator=(const Hero_Descriptor &_other);
	~Hero_Descriptor();

	void Represent(char * _segment);
};

class Hero_Representation : public Representation< Hero_Descriptor >
{
public:
	void Draw(const Hero_Descriptor &_descriptor);

protected:
	Texture *texture = 0;

	Hero_Representation(const char* _texture_path);
	~Hero_Representation();

private:
	Hero_Representation(const Hero_Representation &_other);
	Hero_Representation operator=(const Hero_Representation &_other);
};

class Hero : public Object_Dynamic< Hero_Descriptor >, public Hero_Representation
{
public:
	boost::shared_ptr< Wall > base = 0;
	Collision_Type::Type base_type = Collision_Type::NONE;

	Hero(const Hero_Descriptor& _state, const char* _texture_path);
	~Hero();

	uint8_t movement;
	void Move(const uint8_t &_state);
	void Update(const float& _elapsed_time);

	boost::atomic< bool > disposed;
	void Dispose();

	void Collision_Hero(boost::shared_ptr< Hero > _other, const Collision_Type::Type& _type);
	void Collision_Wall(boost::shared_ptr< Wall > _wall, const Collision_Type::Type& _type);

private:
	Hero(const Hero& _other);
	Hero& operator=(const Hero& _other);
};
#endif