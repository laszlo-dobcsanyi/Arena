#include "Arena.h"

#include <iostream>

#include <boost\foreach.hpp>

#include "Hero.h"
#include "Wall.h"

Arena::Arena(const int& _seed)
: character(0)
{

}

Arena::Arena(const std::string& _file)
{
	character = boost::shared_ptr< Hero >(new Hero(Vector2(5., 4.9f)));

	//

	heroes.data.Add(boost::shared_ptr< Hero >(new Hero(Vector2(320., 320.))));

	//

	walls.Add(boost::shared_ptr< Wall >(new Wall(Vector2(3.5, 2.5), 3.5, 2.5)));
	walls.Add(boost::shared_ptr< Wall >(new Wall(Vector2(6.0, 5.5), 3.0, 2.5)));
	walls.Add(boost::shared_ptr< Wall >(new Wall(Vector2(3.0, 9.5), 3.0, 2.5)));
	walls.Add(boost::shared_ptr< Wall >(new Wall(Vector2(9.5, 12.5), 2.5, 2.5)));
}

Arena::~Arena()
{

}

///

void Arena::Update(const float& _elapsed_time)
{
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

template <class T> void Arena::Update_WallBlock(boost::shared_ptr< Hero > _hero, T _block)
{
	/*BOOST_FOREACH(boost::shared_ptr< Wall > wall, _block->walls)
	{
		Collision_Type wall_collision = wall->Collide(*_hero);
		if (wall_collision != Collision_Type::NONE)
		{
			wall->Collision_Hero(_hero, wall_collision);
			_hero->Collision_Wall(wall, wall_collision);
		}

		BOOST_FOREACH(boost::shared_ptr< Hero > connected, wall->heroes)
		{
			Collision_Type hero_collision = connected->Collide(*_hero);
			if (hero_collision != Collision_Type::NONE)
			{
				_hero->Collision_Hero(connected, hero_collision);
				connected->Collision_Hero(_hero, hero_collision);
			}

			// TODO Objects like item/stance collision
		}
	}*/
}

