#include "Macro"

#include <vector>

#include <boost\bind.hpp>
#include <boost\lexical_cast.hpp>
#include <boost\algorithm\string.hpp>

#include "Core\Processor.h"
#include "Core\Configuration.h"
#include "Network\Gateway.h"
#include "Network\Packet.h"
#include "Network\Connection_Server.h"

Gateway::Gateway(Processor *_processor, const boost::asio::ip::tcp::endpoint &_endpoint) :
	disposed(false),

	data(new char[Configuration::network_packet_size]),
	port_generator(Configuration::network_connections_number),

	processor(_processor),
	gateway(_processor->Service(), _endpoint)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::gateway, "> Gateway @ [" + boost::lexical_cast<std::string>(_endpoint.address()) + ":" + boost::lexical_cast<std::string>(_endpoint.port()) + "] Created!");
	#endif

	thread = boost::thread(boost::bind(&Gateway::Listen, this));
}


void Gateway::Listen()
{
	#ifdef LOGGING
	Logger::Write(LogMask::message, LogObject::gateway, "-> Gateway Listening..");
	#endif

	Connection_Server* connection = new Connection_Server(this);
	gateway.async_accept(connection->TCP_Socket(), boost::bind(&Gateway::Handle_Accept, this, connection, boost::asio::placeholders::error));
}


void Gateway::Handle_Accept(Connection_Server* _connection, const boost::system::error_code &_error)
{
	if (!_error)
	{
		#ifdef LOGGING
		Logger::Write(LogMask::message, LogObject::gateway, "-> Gateway Accepted!");
		#endif

		_connection->Start(Configuration::connection_server_port_offset + port_generator.Next());
	}

	if (!disposed) Listen();
}

void Gateway::Return(const int &_port)
{
	#ifdef LOGGING
	Logger::Write(LogMask::message, LogObject::gateway, "-> Gateway Returning port..");
	#endif

	port_generator.Return(_port - Configuration::connection_server_port_offset);
}

void Gateway::Dispose()
{
	if (disposed) return; disposed = true;

	#ifdef LOGGING
	Logger::Write(LogMask::dispose, LogObject::gateway, "-> Gateway Disposing..");
	#endif

	thread.interrupt();
	thread.join();

	gateway.cancel();
	gateway.close();

	//network_processor->Dispose();

	delete this;

	#ifdef LOGGING
	Logger::Write(LogMask::dispose, LogObject::gateway, "<- Gateway Disposed!");
	#endif
}

Gateway::~Gateway()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::gateway, "-> Destroying Gateway!");
	#endif

	delete[] data;

	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::gateway, "<- Gateway Destroyed!");
	#endif
}