#ifndef ARENA_H
#define ARENA_H

#include <string>

#include <boost\shared_ptr.hpp>

#include "Object_BSP.hpp"
#include "ListProcessable.hpp"

class Wall;
class Hero;

class Arena
{
public:
	boost::shared_ptr< Hero > character = 0;
	ListProcessable< boost::shared_ptr< Wall > > walls;
	ListProcessable< boost::shared_ptr< Hero > > heroes;

	BSP_Tree< boost::shared_ptr< Wall > > *collision_tree = 0;

	Arena(const int &_seed);
	Arena(const std::string &_file);
	~Arena();

	void Update(const float &_elapsed_time);

private:
	Arena(const Arena &_other);
	Arena& operator=(const Arena &_other);

	void Update_Hero(boost::shared_ptr< Hero > _hero, const float &_elapsed_time);
};
#endif