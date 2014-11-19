#include "Macro"

#include <vector>

#include <boost\lexical_cast.hpp>
#include <boost\algorithm\string.hpp>

#include "Core\Configuration.h"
#include "Network\Packet.h"
#include "Network\Gateway.h"
#include "Network\Connection.h"

Connection_Server::Connection_Server(Gateway* _gateway) :
	Connection(_gateway->network_processor->Service()),
	gateway(_gateway)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "< Connection_Server Created!");
	#endif
}

Connection_Server::~Connection_Server()
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "-> Destroying Connection_Server..");
	#endif	

	//gateway->Return(udp_socket.local_endpoint().port());

	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "<- Connection_Server Destroyed!");
	#endif
}

void Connection_Server::Start(const int& _udp_port)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "-> Connection_Server Starting..");
	#endif
	try
	{
		udp_socket.open(boost::asio::ip::udp::v4());
		udp_socket.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(Configuration::gateway_address), _udp_port));
		udp_socket.connect(boost::asio::ip::udp::endpoint(tcp_socket.remote_endpoint().address(), tcp_socket.remote_endpoint().port() + 1));
	}
	catch (const boost::system::system_error &_error)
	{
		#ifdef LOGGING
		Logger::Write(LogObject::connection, LogMask::error, " # Error while binding sockets!\n" + boost::lexical_cast< std::string >(_error.what()));
		#endif

		Dispose();
		return;
	}

	DWORD size = 64 * 1024;
	setsockopt(udp_socket.native(), SOL_SOCKET, SO_SNDBUF, (char *)&size, sizeof(WORD));
	setsockopt(udp_socket.native(), SOL_SOCKET, SO_RCVBUF, (char *)&size, sizeof(WORD));

	Packet port_data(Command::Server::UDP_PORT, boost::lexical_cast< std::string >(_udp_port));
	TCP_Send(&port_data);

	Connection::Start();

	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "<- Connection_Server Started!");
	#endif
}

void Connection_Server::Process(char *_data, size_t _received)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "-> Connection_Server Processing..");
	#endif

	int command = 0x00000000; command |= _data[0] << 24; command |= _data[1] << 16; command |= _data[2] << 8; command |= _data[3];
	std::vector< std::string > arguments; boost::split(arguments, Packet::ToString(_data + 4, _received - 4), boost::is_any_of(";"));

}