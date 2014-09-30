#include "Arena.h"

#include <boost\foreach.hpp>

#include "Hero.h"
#include "Wall.h"
#include "WallBlock.h"

Arena::Arena(const int& _seed)
{

}

Arena::Arena(const std::string& _file)
{
	boost::shared_ptr< WallBlock > block0 = boost::shared_ptr< WallBlock >(new WallBlock());
	block0->walls.push_front(boost::shared_ptr< Wall >(new Wall(0., 32., 640., 0.)));
	block0->walls.push_front(boost::shared_ptr< Wall >(new Wall(0., 640., 32., 32.)));
	block0->Finalize();
	
	boost::shared_ptr< Hero > hero0 = boost::shared_ptr< Hero >(new Hero(Vector2(320., 320.)));

	//
	
	blocks.push_front(block0);

	heroes.push_front(hero0);


	//objects.Add(boost::shared_ptr< Object >(new Wall(0., 32., 640., 0.)));
	//objects.Add(boost::shared_ptr< Object >(new Wall(0., 640., 32., 32.)));
	//objects.Add(boost::shared_ptr< Object >(new Hero(Vector2(640. + 128., 0. - 128.))));
	// case5: 640. + 128., 32. + 128.
	// case6: 0. - 128., 32. + 128.
	// case7: 0. - 128., 0. - 128.
	// case8: 640. + 128., 0. - 128.

}

Arena::~Arena()
{

}

///

void Arena::Update(const float& _elapsed_time)
{
	BOOST_FOREACH(boost::shared_ptr< Hero > hero, heroes)
	{
		hero->Update(_elapsed_time);

		if (hero->base)
		{

		}
		else
		{
			BOOST_FOREACH(boost::shared_ptr< WallBlock > block, blocks)
			{
				Collision_Type block_collision = block->Collide(*hero);
				if (block_collision != Collision_Type::NONE)
				{
					BOOST_FOREACH(boost::shared_ptr< Wall > wall, block->walls)
					{
						Collision_Type wall_collision = wall->Collide(*hero);
						if (wall_collision != Collision_Type::NONE)
						{
							hero->Collision_Wall(wall, wall_collision);
							wall->Collision_Hero(hero, wall_collision);
						}

						BOOST_FOREACH(boost::shared_ptr< Hero > connected, wall->heroes)
						{
							Collision_Type hero_collision = connected->Collide(*hero);
							if (hero_collision != Collision_Type::NONE)
							{
								hero->Collision_Hero(connected, hero_collision);
								connected->Collision_Hero(hero, hero_collision);
							}

							// TODO Objects like item/stance collision
						}
					}
				}
			}
		}

		hero->center = hero->updated_center;
		//hero->Report();
	}

	/*heroes.Process_Adding();

	BOOST_FOREACH(boost::shared_ptr< Hero > hero, heroes.data.list)
	{
	hero->Update(_elapsed_time);
	}

	for (std::list< boost::shared_ptr< Hero > >::const_iterator outer_iterator = heroes.data.list.begin(), outer_end = heroes.data.list.end(); outer_iterator != outer_end; ++outer_iterator)
	{
	std::list< boost::shared_ptr< Hero > >::const_iterator inner_iterator = outer_iterator; inner_iterator++;
	for (std::list< boost::shared_ptr< Hero > >::const_iterator inner_end = heroes.data.list.end(); inner_iterator != inner_end; ++inner_iterator)
	{
	Collision_Type collision = (*outer_iterator)->Collide(*(*inner_iterator));
	if (collision != Collision_Type::NONE)
	{
	(*outer_iterator)->Collision_Hero((*inner_iterator), collision);
	(*inner_iterator)->Collision_Hero((*outer_iterator), collision);
	}
	}

	BOOST_FOREACH(boost::shared_ptr< Wall > wall, walls.list)
	{
	Collision_Type collision = wall->Collide(*(*outer_iterator));
	if (collision != Collision_Type::NONE)
	{
	(*outer_iterator)->Collision_Wall(wall, collision);
	wall->Collision_Hero((*outer_iterator), collision);
	}
	}
	}

	BOOST_FOREACH(boost::shared_ptr< Hero > hero, heroes.data.list)
	{
	hero->center = hero->updated_center;
	hero->Report();
	}

	heroes.Process_Removing();*/
}
