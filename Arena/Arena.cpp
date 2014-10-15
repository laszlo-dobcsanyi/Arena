#include "Arena.h"

#include <string>
#include <fstream>
#include <iostream>
#include <assert.h>

#include <boost\foreach.hpp>

#include "Hero.h"
#include "Wall.h"

Arena::Arena(const int &_seed)
{

}

Arena::Arena(const std::string &_file)
{
	character = boost::shared_ptr< Hero >(new Hero(Vector2(500., 400.), "Textures\\awesomeface.png"));

	//

	for (int i = 0; i < 0; ++i)
	{
		heroes.data.Add(boost::shared_ptr< Hero >(new Hero(Vector2(800., 320.),"Textures\\awesomeface.png")));
	}

	//

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

	collision_tree = new BSP_Tree< boost::shared_ptr< Wall > >(wall_segment);
}

Arena::~Arena()
{

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
		boost::shared_ptr< Wall > wall = collision_tree->Collision(Vector2(_hero->updated_center.x + offsets[stage][0] * _hero->width, _hero->updated_center.y + offsets[stage][1] * _hero->height));
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
	_hero->center = _hero->updated_center;
}


