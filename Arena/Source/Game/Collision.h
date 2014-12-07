#ifndef GAME_COLLISION_HPP
#define GAME_COLLISION_HPP

struct Descriptor;
struct Hero_Descriptor;
struct Wall_Descriptor;

namespace Collision_Type
{
	enum Type
	{
		NONE = 0,
		INSIDE = 1,
		TOP = 2,
		BOTTOM = 3,
		RIGHT = 4,
		LEFT = 5
	};
}

namespace Collision
{
	//template< class T1, class T2 > Collision_Type::Type Resolve(const T1 &_current, const T2 &_other);
	//template< > Collision_Type::Type Resolve< Descriptor, Descriptor >(const Descriptor &_current, const Descriptor &_other);
	Collision_Type::Type Resolve(const Descriptor &_current, const Descriptor_Dynamic &_other);
	/*Collision_Type::Type Resolve(const Wall_Descriptor &_wall, const Hero_Descriptor &_hero)
	{
		return Resolve< Descriptor, Descriptor >(_wall, _hero);
	}*/
	//template< > Collision_Type::Type Resolve< Hero_Descriptor, Wall_Descriptor>(const Hero_Descriptor &_)

	//template< class T1, class T2 > Collision_Type::Type Attachment(const T1 &_current, const T2 &_other);
	Collision_Type::Type Attachment(const Descriptor &_current, const Descriptor &_other);
}
#endif