#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <boost\shared_ptr.hpp>

class Texture;
typedef char GLchar;

struct Vector2
{
	float x, y;

	Vector2(const float& _x, const float& _y) : x(_x), y(_y) { }
	Vector2(const Vector2& _other) : x(_other.x), y(_other.y) { }

	Vector2& operator=(const Vector2& _other) { x = _other.x; y = _other.y; return *this; }
	Vector2 operator+(const Vector2& _other) { return Vector2(x + _other.x, y + _other.y); }
	Vector2 operator*(const float& _value) { return Vector2(x * _value, y * _value); }
};

enum Collision_Type
{
	NONE	= 0,
	INSIDE	= 1,
	TOP		= 2,
	BOTTOM	= 3,
	RIGHT	= 4,
	LEFT	= 5
};

class Object
{
public:
	float width, height;
	Texture* texture;
	Vector2 center, updated_center, velocity, force;

	Object(const Vector2& _center, const float& _width, const float& _height, const GLchar* _texturePath);
	~Object() {  };

	Collision_Type Collide(const Object& _other);
	Collision_Type Attachment(const Object& _other);

private:
	Object(Object& _other);
	Object& operator=(const Object& _other);
};

#endif