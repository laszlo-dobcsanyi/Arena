#ifndef NETWORK_GATEWAY_H
#define NETWORK_GATEWAY_H

#include <boost\asio.hpp>
#include <boost\thread.hpp>
#include <boost\atomic.hpp>

#include "Core\Generator.h"
#include "Game\Lobby.h"
#include "Game\Game_Server.h"

class Processor;
class Connection_Server;

class Gateway
{
public:
	Processor *processor;

	Gateway(Processor *_processor, const boost::asio::ip::tcp::endpoint &_endpoint);
	virtual ~Gateway();

	void Return(const int &_port);

	void Dispose();

private:
	boost::atomic< bool > disposed;

	char* data = 0;
	Generator port_generator;

	boost::asio::ip::tcp::acceptor gateway;

	boost::thread thread;

	void Listen();
	void Handle_Accept(Connection_Server* _connection, const boost::system::error_code &_error);

	Gateway(const Gateway& _other);
	Gateway& operator=(const Gateway* _other);
};

#endif