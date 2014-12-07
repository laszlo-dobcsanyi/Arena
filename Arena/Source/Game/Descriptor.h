#ifndef GAME_DESCRIPTOR_H
#define GAME_DESCRIPTOR_H

#include "Game\Object.hpp"

struct Descriptor
{
public:
	Vector2 center;
	float width, height;

	virtual void Describe(char * _segment) = 0;

protected:
	Descriptor(const Vector2 &_center, const float &_width, const float &_height) :
		center(_center), width(_width), height(_height) { }
	Descriptor(const Descriptor &_other) :
		center(_other.center), width(_other.width), height(_other.height) { }
	Descriptor & operator=(const Descriptor &_other) { center = _other.center; width = _other.width; height = _other.height; return *this; }
	~Descriptor() { }
};


struct Descriptor_Dynamic : public Descriptor
{
public:
	uint8_t movement = 0;

	Vector2 velocity = Vector2(0.f, 0.f), force = Vector2(0.f, 0.f);

	Descriptor_Dynamic(const Vector2 &_center, const float &_width, const float &_height) : Descriptor(_center, _width, _height) { };

	virtual void Describe(char * _segment) { memcpy(_segment, this, sizeof(this)); };
};
#endif