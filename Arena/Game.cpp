#include "Game.h"

#include "Hero.h"
#include "Wall.h"
#include "Arena.h"

Game::Game()
	: objects(boost::shared_ptr< Object >(new Arena()))
{
	objects.Add(boost::shared_ptr< Object >(new Wall(0., 32., 640., 0.)));
	objects.Add(boost::shared_ptr< Object >(new Wall(0., 640., 32., 32.)));
	objects.Add(boost::shared_ptr< Object >(new Hero(Vector2(640. + 128., 0. - 128.))));
	// case5: 640. + 128., 32. + 128.
	// case6: 0. - 128., 32. + 128.
	// case7: 0. - 128., 0. - 128.
	// case8: 640. + 128., 0. - 128.

}

Game::~Game()
{

}

//

void Game::Update(const float& _elapsed_time)
{
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
