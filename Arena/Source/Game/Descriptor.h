#ifndef GAME_DESCRIPTOR_H
#define GAME_DESCRIPTOR_H

#include "Game\Object.hpp"

struct Descriptor
{
public:
	Vector2 center, velocity, force;
	float width, height;

	virtual void Represent(char * _segment) = 0;

protected:
	Descriptor(const Vector2& _center, const float& _width, const float& _height) :
		center(_center), velocity(0., 0.), force(0., 0.), width(_width), height(_height) { }
	Descriptor(const Descriptor &_other) :
		center(_other.center), velocity(_other.velocity), force(_other.force), width(_other.width), height(_other.height) { }
	Descriptor & operator=(const Descriptor &_other) { center = _other.center; velocity = _other.velocity; force = _other.force; width = _other.width; height = _other.height; return *this; }
	~Descriptor() { }
};
#endif