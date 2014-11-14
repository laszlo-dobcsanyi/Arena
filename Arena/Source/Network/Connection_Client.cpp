#include "Macro"

#include <vector>

#include <boost\lexical_cast.hpp>
#include <boost\algorithm\string.hpp>

#include "Network\Packet.h"
#include "Network\Connection.h"

Connection_Client::Connection_Client(boost::asio::io_service &_io_service) :
	Connection(_io_service)
{

}

Connection_Client::~Connection_Client()
{

}

void Connection_Client::Process(char *_data, size_t _received)
{
	int command = 0x00000000; command |= _data[0] << 24; command |= _data[1] << 16; command |= _data[2] << 8; command |= _data[3];
	std::vector< std::string > arguments; boost::split(arguments, Packet::ToString(_data + 4, _received - 4), boost::is_any_of(";"));
}