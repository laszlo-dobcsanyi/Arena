//#undef ERROR
#include "Macro"

#include <boost\lexical_cast.hpp>

#include "Core\Configuration.h"
#include "Game\Hero.h"
#include "Network\Packet.h"
#include "Network\Connection.h"

Connection::Connection(boost::asio::io_service& _io_service) :
	disposed(false),

	tcp_data(new char[Configuration::network_packet_size]),
	udp_data(new char[Configuration::network_packet_size]),

	tcp_socket(_io_service),
	udp_socket(_io_service)
{
	#ifdef LOGGING
	Logger::counter_connections++;
	Logger::Write(LogMask::constructor, LogObject::connection, "\t+ Connection constructor!");
	#endif
}

void Connection::Start()
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "\t-> Starting Connection..");
	#endif

	TCP_Receive();
	UDP_Receive();

	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::connection, "\t<- Connection Started!");
	#endif
}

// TCP

void Connection::TCP_Receive()
{
	tcp_socket.async_receive(boost::asio::buffer(tcp_data, Configuration::network_packet_size),
		boost::bind(&Connection::Handle_TCP_Receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Connection::Handle_TCP_Receive(const boost::system::error_code &_error, size_t _received)
{
	if (_error.value() == 995) return;

	if ((!_error) && (4 <= _received))
	{
		Process(tcp_data, _received);
	}
	else
	{
		#ifdef LOGGING
		Logger::Write(LogMask::error, LogObject::connection, "# Error @ Connection::Handle_TCP_Receive " + _error.message() + "!");
		#endif

		Dispose();
	}

	if (!disposed) TCP_Receive();
}

void Connection::TCP_Send(Packet *_packet)
{
	tcp_socket.async_send(boost::asio::buffer(_packet->data, _packet->size),
		boost::bind(&Connection::Handle_TCP_Send, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Connection::Handle_TCP_Send(const boost::system::error_code &_error, size_t _sent)
{
	if (_error.value() == 995) return;

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
	udp_socket.async_receive(boost::asio::buffer(udp_data, Configuration::network_packet_size),
		boost::bind(&Connection::Handle_UDP_Receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Connection::Handle_UDP_Receive(const boost::system::error_code &_error, size_t _received)
{
	if (_error.value() == 995) return;

	if ((!_error) && (4 <= _received))
	{
		Process(udp_data, _received);
	}
	else
	{
		#ifdef LOGGING
		Logger::Write(LogMask::error, LogObject::connection, "# Error @ Connection::Handle_UDP_Receive " + _error.message() + "!");
		#endif

		Dispose();
	}

	if (!disposed) UDP_Receive();
}

void Connection::UDP_Send(Packet* _packet)
{
	udp_socket.async_send(boost::asio::buffer(_packet->data, _packet->size),
		boost::bind(&Connection::Handle_UDP_Send, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}


void Connection::Handle_UDP_Send(const boost::system::error_code& _error, const size_t& _sent)
{
	if (_error.value() == 995) return;

	if (_error)
	{
		#ifdef LOGGING
		Logger::Write(LogMask::error, LogObject::connection, "# Error @ Connection::Handle_UDP_Send " + _error.message() + "!");
		#endif

		Dispose();
	}
}

void Connection::Dispose()
{
	if (disposed) return; disposed = true;

	#ifdef LOGGING
	Logger::Write(LogMask::dispose, LogObject::connection, "\t-> Disposing Connection" + boost::lexical_cast< std::string >(udp_socket.local_endpoint().port()) + "..");
	#endif

	tcp_socket.close();
	udp_socket.close();

	if (hero)
	{
		hero->Dispose();
		hero.reset();

	}
	else delete this;

	#ifdef LOGGING
	Logger::Write(LogMask::dispose, LogObject::connection, "\t<- Connection Disposed!");
	#endif
}

Connection::~Connection()
{
	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::connection, "\t-> Destroying Connection..");
	#endif

	delete[] tcp_data;
	delete[] udp_data;

	#ifdef LOGGING
	Logger::Write(LogMask::destructor, LogObject::connection, "\t<- Connection Destroyed!");
	Logger::counter_connections--;
	#endif
}

