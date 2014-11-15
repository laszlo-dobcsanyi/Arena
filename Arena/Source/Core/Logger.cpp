#include "Core\Logger.h"

#include "Windows.h"

/*
//bit 0 - foreground blue
//bit 1 - foreground green
//bit 2 - foreground red
//bit 3 - foreground intensity

//bit 4 - background blue
//bit 5 - background green
//bit 6 - background red
//bit 7 - background intensity
static const WORD colors[] = { 0x0F, 0x0C, 0x04, 0x04, 0x0A, 0x02, 0x02, 0x0B, 0x03, 0x03 };
*/

int Logger::mask = 0xFFFFFFFF;
int Logger::object = 0xFFFFFFFF & (~LogObject::bsp_tree) & (~LogObject::wall) & (~LogObject::hero);
HANDLE Logger::console = GetStdHandle(STD_OUTPUT_HANDLE);

typedef unsigned int unsigned_int;
boost::atomic< unsigned_int > Logger::counter_bsp_separator(0);
boost::atomic< unsigned_int > Logger::counter_bsp_node(0);
boost::atomic< unsigned_int > Logger::counter_bsp_tree(0);
boost::atomic< unsigned_int > Logger::counter_list_lockable(0);
boost::atomic< unsigned_int > Logger::counter_list_processable(0);
boost::atomic< unsigned_int > Logger::counter_list_separatable(0);

boost::atomic< unsigned_int > Logger::counter_heroes(0);
boost::atomic< unsigned_int > Logger::counter_walls(0);

boost::atomic< unsigned_int > Logger::counter_textures(0);

boost::atomic< unsigned_int > Logger::counter_connections(0);
boost::atomic< unsigned_int > Logger::counter_packets(0);
boost::atomic< unsigned_int > Logger::counter_packet_pairs(0);

void Logger::Write(const int& _mask, const int& _object, const std::string& _msg)
{
	if ((mask & _mask) && (object & _object))
	{
		//SetConsoleTextAttribute(console, ((0 <= _level) &&(_level <= 9)) ? colors[_level] : 0x0F);
		std::cout << (_msg + "\n");
	}
}

void Logger::Write_Counters()
{
	std::cout << std::endl << ">>Counters<<" << std::endl;
	std::cout << std::endl;
	std::cout << ">BSP_Separators: " << counter_bsp_separator << std::endl;
	std::cout << ">BSP_Nodes: " << counter_bsp_node << std::endl;
	std::cout << ">BSP_Trees: " << counter_bsp_tree << std::endl;
	std::cout << ">List_Lockables: " << counter_list_lockable << std::endl;
	std::cout << ">List_Processables: " << counter_list_processable << std::endl;
	std::cout << ">List_Separatables: " << counter_list_separatable << std::endl;
	std::cout << std::endl;
	std::cout << ">Heroes: " << counter_heroes << std::endl;
	std::cout << ">Walls: " << counter_walls << std::endl;
	std::cout << std::endl;
	std::cout << ">Textures: " << counter_textures << std::endl;
	std::cout << std::endl;
	std::cout << ">Connections: " << counter_connections << std::endl;
	std::cout << ">Packets: " << counter_packets << std::endl;
	std::cout << ">Packet Pairs: " << counter_packet_pairs << std::endl;
}

void Logger::SetColor(const WORD& _color)
{
	SetConsoleTextAttribute(console, _color);
}


