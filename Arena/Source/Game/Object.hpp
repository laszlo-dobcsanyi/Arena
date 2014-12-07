#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <boost\shared_ptr.hpp>

#include "Core\State_Buffer.hpp"

struct Vector2
{
	float x, y;

	Vector2(const float& _x, const float& _y) : x(_x), y(_y) { }
	Vector2(const Vector2& _other) : x(_other.x), y(_other.y) { }

	Vector2& operator=(const Vector2& _other) { x = _other.x; y = _other.y; return *this; }
	Vector2 operator+(const Vector2& _other) { return Vector2(x + _other.x, y + _other.y); }
	Vector2 operator*(const float& _value) { return Vector2(x * _value, y * _value); }
};

template< class State_Descriptor >
class Object
{
protected:
	Object() { }
	~Object() { }

	//Collision_Type Attachment(const Object& _other);

private:
	Object(Object& _other);
	Object& operator=(const Object& _other);
};

template< class State_Descriptor >
class Object_Static : public Object< State_Descriptor >, public State_Descriptor
{
protected:
	Object_Static(const State_Descriptor &_state)
		: State_Descriptor(_state)
	{

	}

	~Object_Static()
	{

	}

private:
	Object_Static(const Object_Static< State_Descriptor > &_other);
	Object_Static< State_Descriptor > & operator=(const Object_Static< State_Descriptor > &_other);
};

template< class State_Descriptor >
class Object_Dynamic : public Object< State_Descriptor >
{
public:
	State_Buffer< State_Descriptor > states;

	virtual void Update(const float& _elapsed_time) = 0;

protected:
	Object_Dynamic(const unsigned int &_state_buffer_size, const State_Descriptor &_state)
		: states(_state_buffer_size, _state)
	{

	}

	~Object_Dynamic()
	{

	}

private:
	Object_Dynamic(const Object_Dynamic< State_Descriptor > &_other);
	Object_Dynamic< State_Descriptor > & operator=(const Object_Dynamic< State_Descriptor > &_other);
};

#endif