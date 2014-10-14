#ifndef ARENA_H
#define ARENA_H

#include <string>

#include <boost\shared_ptr.hpp>

#include "ListProcessable.hpp"

class Wall;
class Hero;

class Arena
{
public:
	boost::shared_ptr< Hero > character;
	ListProcessable< boost::shared_ptr< Wall > > walls;
	ListProcessable< boost::shared_ptr< Hero > > heroes;

	Arena(const int& _seed);
	Arena(const std::string& _file);
	~Arena();

	void Update(const float& _elapsed_time);

private:
	Arena(const Arena& _other);
	Arena& operator=(const Arena& _other);

	template <class T> void Update_WallBlock(boost::shared_ptr< Hero > _hero, T _block);
};
#endif