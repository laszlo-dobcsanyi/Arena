//#undef ERROR

#include <boost\lexical_cast.hpp>

#include "Macro"
#include "Core\Configuration.h"
#include "Game\Hero.h"
#include "Network\Packet.h"
#include "Network\Connection.h"

Connection::Connection(boost::asio::io_service& _io_service) :
	disposed(false),

	tcp_data(new char[Configuration::Get()->network_packet_size]),
	udp_data(new char[Configuration::Get()->network_packet_size]),

	tcp_socket(_io_service),
	udp_socket(_io_service),

	timeout(_io_service, boost::posix_time::seconds(Configuration::Get()->network_timeout))
{
	#ifdef LOGGING
	Logger::counter_connections++;
	Logger::Write(LogMask::constructor, LogObject::connection, "> Connection constructor!");
	#endif
}

void Connection::Start(const int& _udp_port)
{
	#ifdef LOGGING
	Logger::counter_connections++;
	Logger::Write(LogMask::constructor, LogObject::connection, "> Connection starting on port " + boost::lexical_cast< std::string >(_udp_port) + "..");
	#endif

	udp_socket.bind(boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(Configuration::Get()->gateway_address), _udp_port));
	udp_socket.connect(boost::asio::ip::udp::endpoint(tcp_socket.remote_endpoint().address(), tcp_socket.remote_endpoint().port() + 1));

	DWORD size = 64 * 1024;
	setsockopt(udp_socket.native(), SOL_SOCKET, SO_SNDBUF, (char *)&size, sizeof(WORD));
	setsockopt(udp_socket.native(), SOL_SOCKET, SO_RCVBUF, (char *)&size, sizeof(WORD));

	Packet port_data(Command::Server::UDP_PORT, boost::lexical_cast< std::string >(_udp_port));
	TCP_Send(&port_data);

	TCP_Receive();
	UDP_Receive();

	timeout.expires_from_now(boost::posix_time::seconds(Configuration::Get()->network_timeout));
	timeout.async_wait(boost::bind(&Connection::Handle_Timeout, this, boost::asio::placeholders::error));
}

// TCP

void Connection::TCP_Receive()
{
	tcp_socket.async_receive(boost::asio::buffer(tcp_data, Configuration::Get()->network_packet_size),
		boost::bind(&Connection::Handle_TCP_Receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Connection::Handle_TCP_Receive(const boost::system::error_code &_error, size_t _received)
{
	if ((!_error) && (4 <= _received))
	{
		Process(tcp_data, _received);

		timeout.expires_from_now(boost::posix_time::seconds(Configuration::Get()->network_timeout));
		timeout.async_wait(boost::bind(&Connection::Handle_Timeout, this, boost::asio::placeholders::error));
	}
	else
	{
		#ifdef LOGGING
		Logger::Write(LogMask::error, LogObject::connection, "# Error @ Connection::Handle_TCP_Receive " + _error.message() + "!");
		#endif
	}

	TCP_Receive();
}

void Connection::TCP_Send(Packet *_packet)
{
	tcp_socket.async_send(boost::asio::buffer(_packet->data, _packet->size),
		boost::bind(&Connection::Handle_TCP_Send, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Connection::Handle_TCP_Send(const boost::system::error_code &_error, size_t _sent)
{
	if (_error)
	{
		#ifdef LOGGING
		Logger::Write(LogMask::error, LogObject::connection, "# Error @ Connection:Handle_TCP_Send " + _error.message() + "!");
		#endif
	}
}

// UDP

void Connection::UDP_Receive()
{
	udp_socket.async_receive(boost::asio::buffer(udp_data, Configuration::Get()->network_packet_size),
		boost::bind(&Connection::Handle_UDP_Receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Connection::Handle_UDP_Receive(const boost::system::error_code &_error, size_t _received)
{
	if ((!_error) && (4 <= _received))
	{
		Process(udp_data, _received);

		timeout.expires_from_now(boost::posix_time::seconds(Configuration::Get()->network_timeout));
		timeout.async_wait(boost::bind(&Connection::Handle_Timeout, this, boost::asio::placeholders::error));
	}
	else
	{
		#ifdef LOGGING
		Logger::Write(LogMask::error, LogObject::connection, "# Error @ Connection::Handle_UDP_Receive " + _error.message() + "!");
		#endif
	}

	UDP_Receive();
}

void Connection::UDP_Send(Packet* _packet)
{
	udp_socket.async_send(boost::asio::buffer(_packet->data, _packet->size),
		boost::bind(&Connection::Handle_UDP_Send, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}


void Connection::Handle_UDP_Send(const boost::system::error_code& _error, const size_t& _sent)
{
	if (_error)
	{
		#ifdef LOGGING
		Logger::Write(LogMask::error, LogObject::connection, "# Error @ Connection::Handle_UDP_Send " + _error.message() + "!");
		#endif
	}
}

void Connection::Handle_Timeout(const boost::system::error_code& _error)
{
	if (!_error)
	{
		#ifdef LOGGING
		Logger::Write(LogMask::dispose, LogObject::connection, "> Connection" + boost::lexical_cast< std::string >(udp_socket.local_endpoint().port()) + " timeout!");
		#endif

		Dispose();
	}
}

void Connection::Dispose()
{
	if (disposed) return; disposed = true;

	#ifdef LOGGING
	Logger::Write(LogMask::dispose, LogObject::connection, "> Disposing Connection" + boost::lexical_cast< std::string >(udp_socket.local_endpoint().port()) + "..");
	#endif

	tcp_socket.close();
	udp_socket.close();

	if (hero)
	{
		hero->Dispose();
		hero.reset();

	}
	else delete this;
}

Connection::~Connection()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::connection, "> Connection" + boost::lexical_cast< std::string >(udp_socket.local_endpoint().port()) + " destructor..");
	#endif

	delete[] tcp_data;
	delete[] udp_data;

	#ifdef LOGGING
	Logger::counter_connections--;
	#endif
}
