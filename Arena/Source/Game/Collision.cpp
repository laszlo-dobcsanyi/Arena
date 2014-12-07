#include <assert.h>

#include "Macro"
#include "Game\Descriptor.h"
#include "Game\Collision.h"

Collision_Type::Type Collision::Resolve(const Descriptor &_current, const Descriptor &_other)
{
	//   ^
	//   |      6 \ |    1    | / 5
	//   |      ___\|_________|/___
	//   |          |p1       |
	//   |       4  |    0    |  3
	//   |      ____|_______p2|____
	//   |         /|         |\      |
	//   |      7 / |    2    | \ 8
	//   |
	// (0,0)---------------------->

	Vector2 my_p1(_current.center.x - _current.width, _current.center.y + _current.height);
	Vector2 my_p2(_current.center.x + _current.width, _current.center.y - _current.height);
	Vector2 ur_p1(_other.center.x - _other.width, _other.center.y + _other.height);
	Vector2 ur_p2(_other.center.x + _other.width, _other.center.y - _other.height);

	// case 0:
	if (my_p1.x < _other.center.x && _other.center.x < my_p2.x	&&	my_p2.y < _other.center.y && _other.center.y < my_p1.y) return Collision_Type::INSIDE;

	// case 1:
	if (my_p1.y < _other.center.y && my_p1.x <= _other.center.x && _other.center.x <= my_p2.x)
	{
		if (ur_p2.y <= my_p1.y) return Collision_Type::TOP;
		else return  Collision_Type::NONE;
	}

	// case 2:
	if (_other.center.y < my_p2.y && my_p1.x <= _other.center.x && _other.center.x <= my_p2.x)
	{
		if (my_p2.y <= ur_p1.y) return Collision_Type::BOTTOM;
		else return  Collision_Type::NONE;
	}

	// case 3:
	if (my_p2.x < _other.center.x && my_p2.y <= _other.center.y && _other.center.y <= my_p1.y)
	{
		if (ur_p1.x <= my_p2.x) return Collision_Type::RIGHT;
		else return  Collision_Type::NONE;
	}

	// case 4:
	if (_other.center.x < my_p1.x && my_p2.y <= _other.center.y && _other.center.y <= my_p1.y)
	{
		if (my_p1.x <= ur_p2.x) return Collision_Type::LEFT;
		else return  Collision_Type::NONE;
	}

	// case 5:
	if (my_p2.x < _other.center.x && my_p1.y < _other.center.y)
	{
		if (ur_p1.x < my_p2.x && ur_p2.y < my_p1.y)
		{
			float ur_m = _other.velocity.x / _other.velocity.y;
			float my_m = (_other.center.x - my_p2.x) / (_other.center.y - my_p1.y);

			if (ur_m < my_m) return Collision_Type::RIGHT;
			else return Collision_Type::TOP;
		}
		return Collision_Type::NONE;
	}

	// case 6:
	if (_other.center.x < my_p1.x && my_p1.y < _other.center.y)
	{
		if (my_p1.x < ur_p2.x && my_p1.y < ur_p2.y)
		{
			float ur_m = _other.velocity.x / _other.velocity.y;
			float my_m = (_other.center.x - my_p1.x) / (_other.center.y - my_p1.y);

			if (ur_m < my_m) return Collision_Type::TOP;
			else return Collision_Type::LEFT;
		}
		return Collision_Type::NONE;
	}

	// case 7:
	if (_other.center.x < my_p1.x && _other.center.y < my_p2.y)
	{
		if (my_p1.x < ur_p2.x && my_p2.y < ur_p1.y)
		{
			float ur_m = _other.velocity.x / _other.velocity.y;
			float my_m = (_other.center.x - my_p1.x) / (_other.center.y - my_p2.y);

			if (ur_m < my_m) return Collision_Type::LEFT;
			else return Collision_Type::BOTTOM;
		}
		return Collision_Type::NONE;
	}

	// case 8:
	if (my_p2.x < _other.center.x && _other.center.y < my_p2.y)
	{
		if (ur_p1.x < my_p2.x && my_p2.y < ur_p1.y)
		{
			float ur_m = _other.velocity.x / _other.velocity.y;
			float my_m = (_other.center.x - my_p2.x) / (_other.center.y - my_p2.y);

			if (ur_m < my_m) return Collision_Type::BOTTOM;
			else return Collision_Type::RIGHT;
		}
		return Collision_Type::NONE;
	}

	return Collision_Type::NONE;
}

///

Collision_Type::Type Collision::Attachment(const Descriptor &_current, const Descriptor &_other)
{
	Vector2 my_p1(_current.center.x - _current.width, _current.center.y + _current.height);
	Vector2 my_p2(_current.center.x + _current.width, _current.center.y - _current.height);

	// case 1:
	if (my_p2.x + _other.width == _other.center.x)
	{
		if (my_p2.y - _other.height < _other.center.y && _other.center.y < my_p1.y + _other.height) return Collision_Type::RIGHT;
		return Collision_Type::NONE;
	}

	// case 2:
	if (my_p1.y + _other.height == _other.center.y)
	{
		if (my_p1.x - _other.width < _other.center.x && _other.center.x < my_p2.x + _other.width) return Collision_Type::TOP;
		return Collision_Type::NONE;
	}

	// case 3:
	if (my_p1.x - _other.width == _other.center.x)
	{
		if (my_p2.y - _other.height < _other.center.y && _other.center.y < my_p1.y + _other.height) return Collision_Type::LEFT;
		return Collision_Type::NONE;
	}
	return Collision_Type::NONE;
}
