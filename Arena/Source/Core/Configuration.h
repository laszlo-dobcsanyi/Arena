#ifndef CORE_CONFIGURATION_H
#define CORE_CONFIGURATION_H

#include <string>

class Configuration
{
public:
	float			game_update_interval = 1.f / 50;

	int				network_timeout = 5;
	int				network_packet_size = 512;
	unsigned int	network_processor_threads = 4;
	unsigned int	network_connections_number = 4;

	std::string		gateway_address = "192.168.1.102";
	unsigned int	gateway_port = 1425;

	unsigned int	connection_server_port_offset = 40000;

	std::string		connection_client_server_address = gateway_address;
	unsigned int	connection_client_server_port = gateway_port;

	static const Configuration* const Get();
	static const Configuration* Load(const std::string &_file);

private:
	static Configuration* configuration;

	Configuration();

	Configuration(const Configuration &_other);
	Configuration & operator=(const Configuration &_other);
};

#endif