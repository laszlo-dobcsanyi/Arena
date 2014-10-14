#include "Arena.h"

#include <iostream>

#include <boost\foreach.hpp>

#include "Hero.h"
#include "Wall.h"

Arena::Arena(const int& _seed)
{

}

Arena::Arena(const std::string& _file)
{
	character = boost::shared_ptr< Hero >(new Hero(Vector2(5., 4.9f), "Textures\\awesomeface.png"));

	//

	heroes.data.Add(boost::shared_ptr< Hero >(new Hero(Vector2(320., 320.),"Textures\\awesomeface.png")));

	//

	walls.Add(boost::shared_ptr< Wall >(new Wall(Vector2(3.5, 2.5), 3.5, 2.5, "Textures\\wall.png")));
	walls.Add(boost::shared_ptr< Wall >(new Wall(Vector2(6.0, 5.5), 3.0, 2.5, "Textures\\wall.png")));
	walls.Add(boost::shared_ptr< Wall >(new Wall(Vector2(3.0, 9.5), 3.0, 2.5, "Textures\\wall.png")));
	walls.Add(boost::shared_ptr< Wall >(new Wall(Vector2(9.5, 12.5), 2.5, 2.5, "Textures\\wall.png")));
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

