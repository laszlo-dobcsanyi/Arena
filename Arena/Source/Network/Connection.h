#ifndef NETWORK_CONNECTION_H
#define NETWORK_CONNECTION_H

#include <string>

#include <boost\asio.hpp>
#include <boost\thread.hpp>
#include <boost\atomic.hpp>
#include <boost\shared_ptr.hpp>

struct Packet;
class Hero;
class Gateway;

namespace Command
{
	namespace Server
	{
		enum Command_Type
		{
			UDP_PORT = 0,
			GAME_STATE = 1
		};
	}

	namespace Client
	{
		enum Command_Type
		{
			LOGIN = 0
		};
	}
}

class Connection
{
public:
	Connection(boost::asio::io_service &_io_service);
	virtual ~Connection();

	void Start();

	void TCP_Send(Packet *_packet);

	void UDP_Send(Packet *_packet);

	boost::asio::ip::tcp::socket & TCP_Socket() { return tcp_socket; };
	boost::asio::ip::udp::socket & UDP_Socket() { return udp_socket; };

	// TODO this should be pure virtual, right?
	virtual void Dispose();

	virtual void Process(char *_data, size_t _received) = 0;

protected:
	boost::shared_ptr< Hero > hero = 0;

	boost::atomic< bool > disposed;

	// TCP
	char *tcp_data = 0;
	boost::asio::ip::tcp::socket tcp_socket;

	void TCP_Receive();
	void Handle_TCP_Receive(const boost::system::error_code &_error, size_t _received);

	void Handle_TCP_Send(const boost::system::error_code &_error, size_t _sent);

	// UDP
	char *udp_data = 0;
	boost::asio::ip::udp::socket udp_socket;

	void UDP_Receive();
	void Handle_UDP_Receive(const boost::system::error_code &_error, size_t _received);

	void Handle_UDP_Send(const boost::system::error_code &_error, const size_t &_sent);

	// Timeout
	boost::asio::deadline_timer timeout;
	void Handle_Timeout(const boost::system::error_code &_error);

private:
	Connection(const Connection &_other);
	Connection & operator=(const Connection &_other);
};

class Connection_Server : public Connection
{
public:
	Connection_Server(Gateway* gateway);
	virtual ~Connection_Server();

	void Start(const int& _udp_port);

	void Process(char *_data, size_t _received);

private:
	Gateway* gateway;
	Connection_Server(const Connection_Server &_other);
	Connection_Server & operator=(const Connection_Server &_other);
};

class Connection_Client : public Connection
{
public:
	Connection_Client(boost::asio::io_service &_io_service, const boost::asio::ip::tcp::endpoint &_local_endpoint);
	virtual ~Connection_Client();

	void Connect(const boost::asio::ip::tcp::endpoint &_remote_endpoint);
	void Process(char *_data, size_t _received);

private:
	void Handle_Connect(const boost::system::error_code &_error);

	Connection_Client(const Connection_Client &_other);
	Connection_Client & operator=(const Connection_Client &_other);
};
#endif