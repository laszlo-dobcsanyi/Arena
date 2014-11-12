#ifndef NETWORK_CONNECTION_H
#define NETWORK_CONNECTION_H

#include <string>

#include <boost\bind.hpp>
#include <boost\asio.hpp>
#include <boost\atomic.hpp>
#include <boost\shared_ptr.hpp>

struct Packet;
class Character;

namespace Command
{
	namespace Server
	{
		enum Command_Type
		{
			LOGIN_OK = 0,
			REGISTRATE_OK = 1,

			HERO_DATA = 10,
			HERO_WORLD = 11,
			HERO_SPELLS = 12,

			CHARACTER_ENTER = 20,
			CHARACTER_MOVE = 21,
			CHARACTER_LEAVE = 29,

			OBJECT_ADD = 30,
			OBJECT_REMOVE = 39,

			GROUP_INVITATION = 40,
			GROUP_ADD = 41,
			GROUP_LEADER = 42,
			GROUP_LEAVE = 43,

			BATTLE_RELOCATE = 50,

			ERROR_LOGIN = 1000,
			ERROR_REGISTRATE = 1001
		};
	}

	namespace Client
	{
		enum Command_Type
		{
			LOGIN = 0,
			LOGIN_RESPONSE = 1,

			REGISTRATE = 2,
			PING = 3,

			HERO_MOVE = 10,
			HERO_STOP = 11,
			HERO_CAST = 12,

			GROUP_INVITE = 40,
			GROUP_ACCEPT = 41,
			GROUP_DECLINE = 42,

			BATTLE_JOIN = 50
		};
	}
}

class Connection
{

public:
	Connection(boost::asio::io_service &_io_service, const boost::asio::ip::udp::endpoint &_endpoint, const boost::asio::ip::udp::endpoint &_connected_endpoint, const std::string &_name);
	~Connection();

	void Send(Packet *_packet);
	void Send(boost::shared_ptr< Packet > _packet);
	void Send(const int &_command, const std::string &_message);

	inline const boost::asio::ip::udp::endpoint& LocalEndPoint() const { return local_endpoint; };
	inline const boost::asio::ip::udp::socket& Socket() { return socket; };

	void Dispose();

private:
	boost::atomic< bool > disposed;

	char *data;
	std::string name;
	boost::shared_ptr< Character > character;

	boost::asio::ip::udp::socket socket;

	boost::asio::ip::udp::endpoint local_endpoint;
	boost::asio::ip::udp::endpoint remote_endpoint;
	boost::asio::ip::udp::endpoint connected_endpoint;

	boost::asio::deadline_timer timeout;

	std::string ToString(char *_data, unsigned int _size);

	void Receive();

	void HandleReceive(const boost::system::error_code &_error, size_t _received);
	void HandleMessage(size_t _received);
	void HandleSend(const boost::system::error_code &_error, const size_t &_sent);
	void HandleTimeout(const boost::system::error_code &_error);

	Connection(const Connection &_other);
	Connection & operator=(const Connection &_other);
};

#endif