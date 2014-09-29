#ifndef OBJECT_H
#define OBJECT_H

#include <boost\shared_ptr.hpp>

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
	RIGHT	= 1,
	TOP		= 2,
	LEFT	= 3,
	BOTTOM	= 4
};

class Object
{
public:
	boost::shared_ptr< Object > base;
	Collision_Type base_type;

	float width, height;
	Vector2 center, updated_center, velocity;

	Object(const Vector2& _center, const float& _width, const float& _height) : center(_center), width(_width), height(_height), updated_center(_center), velocity(0., 0.), base(0), base_type(Collision_Type::NONE) { }
	~Object() {  };

	virtual void Update(const float& _elapsed_time) { updated_center = center + velocity; }
	virtual void Report() = 0;

	Collision_Type Collide(const Object& _other)
	{
		//   ^
		//   |      6 \ |    2    | / 5
		//   |      ___\|_________|/___
		//   |          |p1       |
		//   |       3  |    0    |  1
		//   |      ____|_______p2|____
		//   |         /|         |\
		//   |      7 / |    4    | \ 8
		//   |
		// (0,0)---------------------->

		Vector2 my_p1(updated_center.x - width, updated_center.y + height);
		Vector2 my_p2(updated_center.x + width, updated_center.y - height);
		Vector2 ur_p1(_other.updated_center.x - _other.width, _other.updated_center.y + _other.height);
		Vector2 ur_p2(_other.updated_center.x + _other.width, _other.updated_center.y - _other.height);

		// case 1:
		if (my_p2.x < _other.updated_center.x && my_p2.y < _other.updated_center.y && _other.updated_center.y < my_p1.y)
		{
			if (ur_p1.x < my_p2.x) return Collision_Type::RIGHT;
			else return  Collision_Type::NONE;
		}

		// case 2:
		if (my_p1.y < _other.updated_center.y && my_p1.x < _other.updated_center.x && _other.updated_center.x < my_p2.x)
		{
			if (ur_p2.y < my_p1.y) return Collision_Type::TOP;
			else return  Collision_Type::NONE;
		}

		// case 3:
		if (_other.updated_center.x < my_p1.x && my_p2.y < _other.updated_center.y && _other.updated_center.y < my_p1.y)
		{
			if (my_p1.x < ur_p2.x) return Collision_Type::LEFT;
			else return  Collision_Type::NONE;
		}

		// case 4:
		if (_other.updated_center.y < my_p2.y && my_p1.x < _other.updated_center.x && _other.updated_center.x < my_p2.x)
		{
			if (my_p2.x < ur_p1.x) return Collision_Type::BOTTOM;
			else return  Collision_Type::NONE;
		}

		// case 5:
		if (my_p2.x < _other.updated_center.x && my_p1.y < _other.updated_center.y)
		{
			if (ur_p1.x < my_p2.x && ur_p2.y < my_p1.y)
			{
				float ur_m = _other.velocity.x / _other.velocity.y;
				float my_m = (_other.updated_center.x - my_p2.x) / (_other.updated_center.y - my_p1.y);

				if (ur_m < my_m) return Collision_Type::RIGHT;
				else return Collision_Type::TOP;
			}
			return Collision_Type::NONE;
		}

		// case6:
		if (_other.updated_center.x < my_p1.x && my_p1.y < _other.updated_center.y)
		{
			if (my_p1.x < ur_p2.x && my_p1.y < ur_p2.y)
			{
				float ur_m = _other.velocity.x / _other.velocity.y;
				float my_m = (_other.updated_center.x - my_p1.x) / (_other.updated_center.y - my_p1.y);

				if (ur_m < my_m) return Collision_Type::TOP;
				else return Collision_Type::LEFT;
			}
			return Collision_Type::NONE;
		}

		// case7:
		if (_other.updated_center.x < my_p1.x && _other.updated_center.y < my_p2.y)
		{
			if (my_p1.x < ur_p2.x && my_p2.y < ur_p1.y)
			{
				float ur_m = _other.velocity.x / _other.velocity.y;
				float my_m = (_other.updated_center.x - my_p1.x) / (_other.updated_center.y - my_p2.y);

				if (ur_m < my_m) return Collision_Type::LEFT;
				else return Collision_Type::BOTTOM;
			}
			return Collision_Type::NONE;
		}

		// case8:
		if ( my_p2.x < _other.updated_center.x && _other.updated_center.y < my_p2.y)
		{
			if (ur_p1.x < my_p2.x && my_p2.y < ur_p1.y)
			{
				float ur_m = _other.velocity.x / _other.velocity.y;
				float my_m = (_other.updated_center.x - my_p2.x) / (_other.updated_center.y - my_p2.y);

				if (ur_m < my_m) return Collision_Type::BOTTOM;
				else return Collision_Type::RIGHT;
			}
			return Collision_Type::NONE;
		}

		// TODO CENTER?
		return Collision_Type::NONE;
	}

private:
	Object(Object& _other);
	Object& operator=(const Object& _other);
};

#endif