#include "Source\Game\Arena.h"

#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>

#include <boost\random.hpp>
#include <boost\foreach.hpp>
#include <boost\lexical_cast.hpp>

#include "Source\Macro"
#include "Source\Game\Hero.h"
#include "Source\Game\Wall.h"

Arena::Arena(const int &_seed)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::arena, "+> Creating Generated Arena with seed " + boost::lexical_cast< std::string >(_seed) + "..");
	#endif

	character = boost::shared_ptr< Hero >(new Hero(Vector2(500., 400.), "Textures\\awesomeface.png"));
}

Arena::Arena(const std::string &_file)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::arena, "+> Creating Constructed Arena from " + _file + "..");
	#endif

	character = boost::shared_ptr< Hero >(new Hero(Vector2(600., 400.), "Textures\\awesomeface.png"));

	for (int i = 0; i < 0; ++i)
	{
		heroes.data.Add(boost::shared_ptr< Hero >(new Hero(Vector2(800., 320.),"Textures\\awesomeface.png")));
	}

	//

	#ifdef LOGGING
	Logger::Write(LogMask::message, LogObject::arena, "\t:> Arena: Loading data..");
	#endif

	SLL< boost::shared_ptr< Wall > > *wall_segment = new SLL< boost::shared_ptr< Wall > >();

	std::ifstream data(_file); assert(data.is_open());
	while (data.good())
	{
		float x1, y1, x2, y2;	data >> x1 >> y1 >> x2 >> y2;
		std::string texture;	data >> texture;
		boost::shared_ptr< Wall > wall = boost::shared_ptr< Wall >(new Wall(Vector2(x1, y1), Vector2(x2, y2), texture.c_str()));

		walls.data.Add(wall);
		wall_segment->Insert_Last(wall);
	}
	data.close();

	#ifdef LOGGING
	Logger::Write(LogMask::message, LogObject::arena, "\t:> Arena: Creating BSP Tree..");
	#endif

	collision_tree = new BSP_Tree< boost::shared_ptr< Wall > >(wall_segment);
}

Arena::~Arena()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::arena, "<- Destroying Arena..");
	#endif
}

///

void Arena::Update(const float &_elapsed_time)
{
	Update_Hero(character, _elapsed_time);
	BOOST_FOREACH(boost::shared_ptr< Hero > hero, heroes.data.list)
	{
		Update_Hero(hero, _elapsed_time);
	}

	/*BOOST_FOREACH(boost::shared_ptr< Hero > hero, heroes)
	{
		hero->Update(_elapsed_time);

		if (hero->base)
		{
			Update_WallBlock< WallBlock* >(hero, hero->base->block);
		}
		else
		{
			BOOST_FOREACH(boost::shared_ptr< WallBlock > block, blocks)
			{
				Collision_Type block_collision = block->Collide(*hero);
				if (block_collision != Collision_Type::NONE)
				{
					Update_WallBlock< boost::shared_ptr< WallBlock > >(hero, block);
				}
			}
		}

		hero->center = hero->updated_center;
		//hero->Report();
	}*/
}

void Arena::Update_Hero(boost::shared_ptr< Hero > _hero, const float &_elapsed_time)
{
	_hero->Update(_elapsed_time);
	int offsets[4][2] = { { -1, -1 }, { -1, +1 }, { +1, -1 }, { +1, +1 } };
	for (unsigned int stage = 0; stage < 4; ++stage)
	{
		boost::shared_ptr< Wall > wall = collision_tree->Collision(Vector2(_hero->updated_center.x + offsets[stage][0] * (_hero->width + 1.f), _hero->updated_center.y + offsets[stage][1] * (_hero->height + 1.f)));
		if (wall)
		{
			Collision_Type collision = wall->Collide(*_hero);
			if (collision != Collision_Type::NONE)
			{
				wall->Collision_Hero(_hero, collision);
				_hero->Collision_Wall(wall, collision);
			}
		}
	}

	if (_hero->base)
	{
		Collision_Type collision = _hero->base->Attachment(*_hero);
		if (collision != _hero->base_type)
		{
			_hero->base_type = collision;
			_hero->Move(_hero->movement);
			if (collision == Collision_Type::NONE) _hero->base = 0;
		}
	}
	_hero->center = _hero->updated_center;
}


