#include <vector>

#include <boost\bind.hpp>
#include <boost\lexical_cast.hpp>
#include <boost\algorithm\string.hpp>

#include "Macro"
#include "Core\Processor.h"
#include "Core\Configuration.h"
#include "Network\Gateway.h"
#include "Network\Packet.h"
#include "Network\Connection.h"

extern Processor* network_service;

Gateway::Gateway(const boost::asio::ip::tcp::endpoint &_endpoint) :
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
	boost::shared_ptr< Connection_Server > connection = boost::shared_ptr< Connection_Server >(new Connection_Server(network_service->Service()));
	gateway.async_accept(connection->TCP_Socket(), boost::bind(&Gateway::Handle_Accept, this, connection, boost::asio::placeholders::error));
}


void Gateway::Handle_Accept(boost::shared_ptr< Connection > _connection, const boost::system::error_code &_error)
{
	if (!_error)
	{
		_connection->Start(40000 + port_generator.Next());
	}

	Listen();
}