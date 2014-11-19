#ifndef NETWORK_CONNECTION_SERVER_H
#define NETWORK_CONNECTION_SERVER_H

#include "Network\Connection.h"

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
#endif