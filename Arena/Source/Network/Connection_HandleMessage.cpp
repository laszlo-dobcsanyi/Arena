#include "Macro"

#include <vector>

#include <boost\lexical_cast.hpp>
#include <boost\algorithm\string.hpp>

#include "Network\Connection.h"

std::string Connection::ToString(char* _data, unsigned int _size)
{
	std::string value = "";
	for (unsigned int current = 0; current < _size; ++current) value += _data[current];
	return value;
}

void Connection::HandleMessage(size_t _received)
{
	int command = 0x00000000; command |= data[0] << 24; command |= data[1] << 16; command |= data[2] << 8; command |= data[3];
	std::vector<std::string> arguments; boost::split(arguments, ToString(data + 4, _received - 4), boost::is_any_of(";"));

}