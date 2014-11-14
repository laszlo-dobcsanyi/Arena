#ifndef NETWORK_GATEWAY_H
#define NETWORK_GATEWAY_H

#include <boost\asio.hpp>
#include <boost\thread.hpp>
#include <boost\shared_ptr.hpp>

#include "Core\Generator.h"

class Connection;

class Gateway
{
public:
	Gateway(const boost::asio::ip::tcp::endpoint &_endpoint);

private:
	char* data = 0;
	Generator port_generator;

	boost::asio::ip::tcp::acceptor gateway;
	boost::thread thread;

	void Listen();
	void Handle_Accept(boost::shared_ptr< Connection > _connection, const boost::system::error_code &_error);

	Gateway(const Gateway& _other);
	Gateway& operator=(const Gateway* _other);
};

#endif