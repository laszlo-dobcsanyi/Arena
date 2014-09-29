#include "Game.h"

Game::Game()
: objects(new Object(Vector2(0, 0), 0, 0))
{

}

Game::~Game()
{

}

//

void Game::Update(const float& _elapsed_time)
{
	heroes.Process_Adding();

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

	heroes.Process_Removing();
}
