#ifndef NETWORK_GATEWAY_H
#define NETWORK_GATEWAY_H

#include <boost\asio.hpp>
#include <boost\thread.hpp>

#include "Core\Generator.h"

class Gateway
{
public:
	Gateway(const boost::asio::ip::udp::endpoint &_endpoint);

private:
	char* data = 0;
	Generator port_generator;

	boost::asio::ip::udp::socket gateway;
	boost::thread thread;

	boost::asio::ip::udp::endpoint connected_endpoint;

	Gateway(const Gateway& _other);
	Gateway& operator=(const Gateway* _other);

	std::string ToString(char* _data, unsigned int _size);

	void Listen();
	void HandleReceive(const boost::system::error_code& _error, const size_t& _received);
	void HandleSend(const boost::system::error_code& _error, const size_t& _sent);
};

#endif