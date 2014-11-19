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
		generator			= 1 << 2,
		bsp_tree			= 1 << 3,
		list_lockable		= 1 << 4,
		list_processable	= 1 << 5,
		list_separatable	= 1 << 6,

		arena				= 1 << 7,
		game				= 1 << 8,
		lobby				= 1 << 9,
		hero				= 1 << 10,
		object				= 1 << 11,
		wall				= 1 << 12,

		camera				= 1 << 13,
		input_handler		= 1 << 14,
		main_window			= 1 << 15,
		render				= 1 << 16,
		shader				= 1 << 17,
		texture				= 1 << 18,

		gateway				= 1 << 19,
		connection			= 1 << 20
	};
};

class Logger
{
public:
	static int mask;
	static int object;

	typedef unsigned int unsigned_int;

	static boost::atomic< unsigned_int > counter_bsp_separator;
	static boost::atomic< unsigned_int > counter_bsp_node;
	static boost::atomic< unsigned_int > counter_bsp_tree;
	static boost::atomic< unsigned_int > counter_list_lockable;
	static boost::atomic< unsigned_int > counter_list_processable;
	static boost::atomic< unsigned_int > counter_list_separatable;

	static boost::atomic< unsigned_int > counter_heroes;
	static boost::atomic< unsigned_int > counter_walls;

	static boost::atomic< unsigned_int > counter_textures;

	static boost::atomic< unsigned_int > counter_connections;
	static boost::atomic< unsigned_int > counter_packets;
	static boost::atomic< unsigned_int > counter_packet_pairs;

	static void Write(const int& _mask, const int& _object, const std::string& _msg);
	static void Write_Counters();
	static void SetColor(const unsigned short& _color);

private:
	static void* console;

	Logger();
};

#endif