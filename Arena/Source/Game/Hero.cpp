#include "Game\Hero.h"

#include <iostream>

#include "Macro"
#include "Game\Wall.h"

/// Constructor/Destructor
Hero::Hero(const Vector2& _center, const GLchar* _texturePath)
	: Object(_center, 32, 32, _texturePath),
	  movement(0)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::hero, "\t+> Creating Hero..");
	Logger::counter_heroes++;
	#endif

	Move(0);
}

Hero::~Hero()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::hero, "\t<- Destroying Hero..");
	Logger::counter_heroes--;
	#endif
}

///

void Hero::Update(const float& _elapsed_time)
{
	if (base_type != Collision_Type::NONE)
	{
		if (!(movement & Hero_Movement::RIGHT) && 0.f < velocity.x) velocity.x = velocity.x < 1.f ? 0.f : velocity.x * 0.95f;
		if (!(movement & Hero_Movement::LEFT) && velocity.x < 0.f) velocity.x = -1.f < velocity.x ? 0.f : velocity.x * 0.95f;
	}

	const float max_speed = 64.f;
	if (max_speed < abs(velocity.x)) velocity.x = velocity.x < 0.f ? -max_speed : max_speed;
	if (max_speed < abs(velocity.y)) velocity.y = velocity.y < 0.f ? -max_speed : max_speed;

	velocity = velocity + (force * _elapsed_time);
	updated_center = center + velocity;
}

void Hero::Move(const uint8_t &_state)
{
	const float speed = 16.f;
	switch (base_type)
	{
		case Collision_Type::NONE:
		force = Vector2(0., -speed);
		if (!(movement & Hero_Movement::RIGHT) && _state & Hero_Movement::RIGHT)	{ force.x += +speed; movement |= Hero_Movement::RIGHT; }
		if (!(movement & Hero_Movement::LEFT) && _state & Hero_Movement::LEFT)		{ force.x += -speed; movement |= Hero_Movement::LEFT; }
		break;

		case Collision_Type::RIGHT:
		force = Vector2(0., -speed);
		if (!(movement & Hero_Movement::UP) && _state & Hero_Movement::UP)			{ force.y += +speed / 2.f; movement |= Hero_Movement::UP; }
		if (!(movement & Hero_Movement::DOWN) && _state & Hero_Movement::DOWN)		{ force.y += -speed / 2.f; movement |= Hero_Movement::DOWN; }
		if (!(movement & Hero_Movement::JUMP) && _state & Hero_Movement::JUMP)		{ if (velocity.y <= 0.f) { force = force + Vector2(+speed * 24, +speed * 32); movement |= Hero_Movement::JUMP; } }
		break;

		case Collision_Type::TOP:
		force = Vector2(0., 0.);
		if (!(movement & Hero_Movement::RIGHT) && _state & Hero_Movement::RIGHT)	{ force.x += +speed; movement |= Hero_Movement::RIGHT; }
		if (!(movement & Hero_Movement::LEFT) && _state & Hero_Movement::LEFT)		{ force.x += -speed; movement |= Hero_Movement::LEFT; }
		if (!(movement & Hero_Movement::JUMP) && _state & Hero_Movement::JUMP)		{ if (velocity.y <= 0.f) { force.y += +speed * 32; movement |= Hero_Movement::JUMP; } }
		break;

		case Collision_Type::LEFT:
		force = Vector2(0., -speed);
		if (!(movement & Hero_Movement::UP) && _state & Hero_Movement::UP)			{ force.y += +speed / 2.f; movement |= Hero_Movement::UP; }
		if (!(movement & Hero_Movement::DOWN) && _state & Hero_Movement::DOWN)		{ force.y += -speed / 2.f; movement |= Hero_Movement::DOWN; }
		if (!(movement & Hero_Movement::JUMP) && _state & Hero_Movement::JUMP)		{ if (velocity.y <= 0.f) { force = force + Vector2(-speed * 24, +speed * 32); movement |= Hero_Movement::JUMP; } }
		break;

		case Collision_Type::BOTTOM:
		force = Vector2(0., -speed);
		break;
	}

	if (movement & Hero_Movement::UP && !(_state & Hero_Movement::UP))			{ movement &= ~Hero_Movement::UP; }
	if (movement & Hero_Movement::DOWN && !(_state & Hero_Movement::DOWN))		{ movement &= ~Hero_Movement::DOWN; }
	if (movement & Hero_Movement::RIGHT && !(_state & Hero_Movement::RIGHT))	{ movement &= ~Hero_Movement::RIGHT; }
	if (movement & Hero_Movement::LEFT && !(_state & Hero_Movement::LEFT))		{ movement &= ~Hero_Movement::LEFT; }
	if (movement & Hero_Movement::JUMP && !(_state & Hero_Movement::JUMP))		{ movement &= ~Hero_Movement::JUMP; }
}

///

void Hero::Collision_Hero(boost::shared_ptr< Hero > _other, const Collision_Type& _type)
{

}

void Hero::Collision_Wall(boost::shared_ptr< Wall > _wall, const Collision_Type& _type)
{
	if (base)
	{
		if (_type < base_type)
		{
			base = _wall;
			base_type = _type;
		}
	}
	else
	{
		if (base_type != Collision_Type::BOTTOM)
		{
			base = _wall;
			base_type = _type;
		}
	}

	//std::cout << "Hero COLLISION: " << _type << " : C [" << updated_center.x << ":" << updated_center.y << "] V [" << velocity.x << ":" << velocity.y << "]" << std::endl;
}
