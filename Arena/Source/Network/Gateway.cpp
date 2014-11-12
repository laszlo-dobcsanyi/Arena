#include <vector>


#include <boost\bind.hpp>
#include <boost\lexical_cast.hpp>
#include <boost\algorithm\string.hpp>

#include "Macro"
#include "Core\Configuration.h"
#include "Core\Processor.h"
#include "Network\Gateway.h"
#include "Network\Packet.h"
#include "Network\Connection.h"

extern Processor* network_service;

Gateway::Gateway(const boost::asio::ip::udp::endpoint& _endpoint) :
	data(new char[Configuration::Get()->network_packet_size]),
	port_generator(Configuration::Get()->characters_number),

	gateway(network_service->Service(), _endpoint),
	thread(boost::bind(&Gateway::Listen, this))
{
	#ifdef LOGGING
	Logger::Write(LogMask::initialize, LogObject::gateway, "> Gateway @ [" + boost::lexical_cast<std::string>(_endpoint.address()) + ":" + boost::lexical_cast<std::string>(_endpoint.port()) + "] created!");
	#endif
}

void Gateway::Listen()
{
	gateway.async_receive_from(boost::asio::buffer(data, Configuration::Get()->network_packet_size), connected_endpoint,
		boost::bind(&Gateway::HandleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

std::string Gateway::ToString(char* _data, unsigned int _size)
{
	std::string value = "";
	for (unsigned int current = 0; current < _size; ++current) value += _data[current];
	return value;
}

void Gateway::HandleReceive(const boost::system::error_code& _error, const size_t& _received)
{
	if ((!_error) && (0 < _received))
	{
		int command = 0x00000000; command |= data[0] << 24; command |= data[1] << 16; command |= data[2] << 8; command |= data[3];
		std::vector< std::string > arguments; boost::split(arguments, ToString(data + 4, _received - 4), boost::is_any_of(";"));

		if (command == Command::Client::LOGIN)
		{
			Connection* connection = new Connection(network_service->Service(),
				boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(Configuration::Get()->gateway_address), 40000 + port_generator.Next()), connected_endpoint,
				arguments[0]);

			#ifdef LOGGING
			Logger::Write(LogMask::message, LogObject::gateway, "> Gateway sending packet..");
			#endif

			Packet packet(Command::Server::LOGIN_OK, boost::lexical_cast<std::string>(connection->LocalEndPoint().port()));
			gateway.async_send_to(boost::asio::buffer(packet.data, packet.size), connected_endpoint,
				boost::bind(&Gateway::HandleSend, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
		}
	}
	else
	{
		#ifdef LOGGING
		Logger::Write(LogMask::error, LogObject::gateway, "# Error @ Gateway::HandleReceive " + _error.message() + " (" + boost::lexical_cast<std::string>(_received)+") from [" +
			boost::lexical_cast<std::string>(connected_endpoint.address()) + ":" + boost::lexical_cast<std::string>(connected_endpoint.port()) + "]!\n");
		#endif
	}

	Listen();
}

void Gateway::HandleSend(const boost::system::error_code& _error, const size_t& _sent)
{
	if (_error)
	{
		#ifdef LOGGING
		Logger::Write(LogMask::error, LogObject::gateway, "# Error @ Gateway:HandleSend " + _error.message());
		#endif
	}
}