#ifndef CORE_LOGGER_H
#define CORE_LOGGER_H

#include <iostream>
#include <string>

#include <boost\atomic.hpp>

namespace LogMask
{
	enum LogMask_Enum
	{
		constructor		= 1 << 1,
		destructor		= 1 << 2,
		dispose			= 1 << 3,
		error			= 1 << 4,
		fatal_error		= 1 << 5,
		message			= 1 << 6,
		initialize		= 1 << 7,
		special			= 1 << 8
	};
};

namespace LogObject
{
	enum LogObject_Enum
	{
		core				= 1 << 1,
		bsp_tree			= 1 << 2,
		list_lockable		= 1 << 3,
		list_processable	= 1 << 4,
		list_separatable	= 1 << 5,

		arena	= 1 << 6,
		game	= 1 << 7,
		hero	= 1 << 8,
		object	= 1 << 9,
		wall	= 1 << 10,

		camera			= 1 << 11,
		input_handler	= 1 << 12,
		main_window		= 1 << 13,
		render			= 1 << 14,
		shader			= 1 << 15,
		texture			= 1 << 16
	};
};

class Logger
{
public:
	static int mask;
	static int object;

	typedef unsigned int unsigned_int;

	static boost::atomic< unsigned_int > counter_bsp_tree;
	static boost::atomic< unsigned_int > counter_list_lockable;
	static boost::atomic< unsigned_int > counter_list_processable;
	static boost::atomic< unsigned_int > counter_list_separatable;

	//static boost::atomic< unsigned_int > counter_packets;
	//static boost::atomic< unsigned_int > counter_packet_pairs;

	static boost::atomic< unsigned_int > counter_heroes;
	static boost::atomic< unsigned_int > counter_walls;

	static boost::atomic< unsigned_int > counter_textures;

	static void Write(const int& _mask, const int& _object, const std::string& _msg);
	static void SetColor(const unsigned short& _color);

private:
	static void* console;

	Logger();
};

#endif