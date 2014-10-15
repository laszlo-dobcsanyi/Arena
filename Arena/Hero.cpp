#include "Hero.h"

#include <iostream>

#include "Wall.h"

/// Constructor/Destructor
Hero::Hero(const Vector2& _center, const GLchar* _texturePath)
	: Object(_center, 32, 32, _texturePath),
	  movement(0)
{

}

Hero::~Hero()
{

}

///

void Hero::Update(const float& _elapsed_time)
{
	velocity = velocity + (force * _elapsed_time);
	updated_center = center + velocity;
}

void Hero::Move(const uint8_t &_state)
{
	const float speed = 12.f;
	switch (base_type)
	{
		// Free fall
		case Collision_Type::NONE:
		force = Vector2(0., -speed / 8.);
		if (!(movement & Hero_Movement::RIGHT) && _state & Hero_Movement::RIGHT)	{ velocity.x += +speed; movement |= Hero_Movement::RIGHT; }
		if (movement & Hero_Movement::RIGHT && !(_state & Hero_Movement::RIGHT))	{ velocity.x += -speed; movement &= ~Hero_Movement::RIGHT; }
		if (!(movement & Hero_Movement::LEFT) && _state & Hero_Movement::LEFT)		{ velocity.x += -speed; movement |= Hero_Movement::LEFT; }
		if (movement & Hero_Movement::LEFT && !(_state & Hero_Movement::LEFT))		{ velocity.x += +speed; movement &= ~Hero_Movement::LEFT; }
		break;

		case Collision_Type::RIGHT:
		force = Vector2(0., -speed);
		if (!(movement & Hero_Movement::UP) && _state & Hero_Movement::UP)			{ velocity.y += -speed / 4.; movement |= Hero_Movement::UP; }
		if (movement & Hero_Movement::UP && !(_state & Hero_Movement::UP))			{ velocity.y += +speed / 4.; movement &= ~Hero_Movement::UP; }
		if (!(movement & Hero_Movement::DOWN) && _state & Hero_Movement::DOWN)		{ velocity.y += +speed / 4.; movement |= Hero_Movement::DOWN; }
		if (movement & Hero_Movement::DOWN && !(_state & Hero_Movement::DOWN))		{ velocity.y += -speed / 4.; movement &= ~Hero_Movement::DOWN; }
		break;

		case Collision_Type::TOP:
		force = Vector2(0., 0.);
		if (!(movement & Hero_Movement::RIGHT) && _state & Hero_Movement::RIGHT)	{ velocity.x += +speed; movement |= Hero_Movement::RIGHT; }
		if (movement & Hero_Movement::RIGHT && !(_state & Hero_Movement::RIGHT))	{ velocity.x += -speed; movement &= ~Hero_Movement::RIGHT; }
		if (!(movement & Hero_Movement::LEFT) && _state & Hero_Movement::LEFT)		{ velocity.x += -speed; movement |= Hero_Movement::LEFT; }
		if (movement & Hero_Movement::LEFT && !(_state & Hero_Movement::LEFT))		{ velocity.x += +speed; movement &= ~Hero_Movement::LEFT; }
		if (!(movement & Hero_Movement::JUMP) && _state & Hero_Movement::JUMP)		{ velocity.y += -2*speed; movement |= Hero_Movement::LEFT; }
		if (movement & Hero_Movement::JUMP && !(_state & Hero_Movement::JUMP))		{ velocity.y += +2*speed; movement &= ~Hero_Movement::LEFT; }
		break;

		case Collision_Type::LEFT:
		force = Vector2(0., -speed);
		if (!(movement & Hero_Movement::UP) && _state & Hero_Movement::UP)			{ velocity.y += -speed / 4.; movement |= Hero_Movement::UP; }
		if (movement & Hero_Movement::UP && !(_state & Hero_Movement::UP))			{ velocity.y += +speed / 4.; movement &= ~Hero_Movement::UP; }
		if (!(movement & Hero_Movement::DOWN) && _state & Hero_Movement::DOWN)		{ velocity.y += +speed / 4.; movement |= Hero_Movement::DOWN; }
		if (movement & Hero_Movement::DOWN && !(_state & Hero_Movement::DOWN))		{ velocity.y += -speed / 4.; movement &= ~Hero_Movement::DOWN; }
		break;

		case Collision_Type::BOTTOM:
		force = Vector2(0., -speed);
		break;
	}
}


void Hero::Report()
{
	std::cout << "Hero C [" << center.x << ":" << center.y << "] V [" << velocity.x << ":" << velocity.y << "]" << std::endl;
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
		//if (base_type != Collision_Type::BOTTOM)
		{
			base = _wall;
			base_type = _type;
		}
	}

	//std::cout << "Hero COLLISION: " << _type << " : C [" << updated_center.x << ":" << updated_center.y << "] V [" << velocity.x << ":" << velocity.y << "]" << std::endl;
}
