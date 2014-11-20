#ifndef NETWORK_CONNECTION_CLIENT_H
#define NETWORK_CONNECTION_CLIENT_H

#include <boost\atomic.hpp>

#include "Network\Connection.h"

class Connection_Client : public Connection
{
public:
	Connection_Client(boost::asio::io_service &_io_service, const boost::asio::ip::tcp::endpoint &_local_endpoint);

	void Connect(const boost::asio::ip::tcp::endpoint &_remote_endpoint);

	void Process(char *_data, size_t _received);

	void Dispose();

	virtual ~Connection_Client();

private:
	boost::atomic< bool > disposed;

	void Handle_Connect(const boost::system::error_code &_error);

	Connection_Client(const Connection_Client &_other);
	Connection_Client & operator=(const Connection_Client &_other);
};
#endif