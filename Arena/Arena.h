#ifndef ARENA_H
#define ARENA_H

#include <string>
#include <forward_list>

#include <boost\shared_ptr.hpp>

class Hero;
class WallBlock;

class Arena
{
public:
	std::forward_list< boost::shared_ptr< Hero > > heroes;
	std::forward_list< boost::shared_ptr< WallBlock > > blocks;

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