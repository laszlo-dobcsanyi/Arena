#include "Macro"

#include <vector>
#include <string>

#include <boost\bind.hpp>
#include <boost\lexical_cast.hpp>
#include <boost\algorithm\string.hpp>

#include "Network\Packet.h"
#include "Network\Connection_Client.h"

Connection_Client::Connection_Client(boost::asio::io_service &_io_service, const boost::asio::ip::tcp::endpoint &_local_endpoint) :
	Connection(_io_service),

	disposed(false)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "+> Creating Connection_Client..");
	#endif

	try
	{
		tcp_socket.open(boost::asio::ip::tcp::v4());
		tcp_socket.bind(_local_endpoint);
	}
	catch (const boost::system::system_error &_error)
	{
		#ifdef LOGGING
		Logger::Write(LogObject::connection, LogMask::error, " # Error while binding TCP socket!\n" + boost::lexical_cast< std::string >(_error.what()));
		#endif

		Dispose();
		return;
	}

	try
	{
		udp_socket.open(boost::asio::ip::udp::v4());
		udp_socket.bind(boost::asio::ip::udp::endpoint(tcp_socket.local_endpoint().address(), tcp_socket.local_endpoint().port() + 1));
	}
	catch (const boost::system::system_error &_error)
	{
		#ifdef LOGGING
		Logger::Write(LogObject::connection, LogMask::error, " # Error while binding UDP socket!\n" + boost::lexical_cast< std::string >(_error.what()));
		#endif

		Dispose();
		return;
	}


	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "<+ Connection_Client Created!");
	#endif
}


void Connection_Client::Connect(const boost::asio::ip::tcp::endpoint &_remote_endpoint)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "-> Connection_Client Connecting..");
	#endif

	tcp_socket.async_connect(_remote_endpoint, boost::bind(&Connection_Client::Handle_Connect, this, boost::asio::placeholders::error));
}

void Connection_Client::Handle_Connect(const boost::system::error_code &_error)
{
	if (!_error)
	{
		#ifdef LOGGING
		Logger::Write(LogMask::constructor, LogObject::connection, "<- Connection_Client Connected!");
		#endif

		Start();
	}
	else
	{
		#ifdef LOGGING
		Logger::Write(LogObject::connection, LogMask::error, " # Connection_Client failed to connect to server (TCP)!");
		#endif

		Dispose();
	}
}

void Connection_Client::Process(char *_data, size_t _received)
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "-> Connection_Client Processing..");
	#endif

	int command = 0x00000000; command |= _data[0] << 24; command |= _data[1] << 16; command |= _data[2] << 8; command |= _data[3];
	std::vector< std::string > arguments; boost::split(arguments, Packet::ToString(_data + 4, _received - 4), boost::is_any_of(";"));

	switch (command)
	{
		case Command::Server::UDP_PORT:
			if (arguments.size() == 1) udp_socket.connect(boost::asio::ip::udp::endpoint(tcp_socket.remote_endpoint().address(), boost::lexical_cast<int>(arguments[0].data())));
			else
			{
				#ifdef LOGGING
				Logger::Write(LogObject::connection, LogMask::error, " # Wrong argument count @ Connection_Client::Process - UDP_PORT!");
				#endif
			}
			break;
	default:
		break;
	}
}

void Connection_Client::Dispose()
{
	if (disposed) return; disposed = true;

	#ifdef LOGGING
	Logger::Write(LogMask::dispose, LogObject::connection, "-> Disposing Connection_Client..");
	#endif

	Connection::Dispose();

	#ifdef LOGGING
	Logger::Write(LogMask::dispose, LogObject::connection, "<- Connection_Client Disposed!");
	#endif
}

Connection_Client::~Connection_Client()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::connection, "<- Connection_Client Destroyed!");
	#endif
}