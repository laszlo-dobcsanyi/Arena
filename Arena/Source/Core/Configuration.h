#ifndef CORE_CONFIGURATION_H
#define CORE_CONFIGURATION_H

#include <string>

class Configuration
{
public:
	float			game_update_interval = 1.f / 50;
	unsigned int	characters_number;

	std::string		gateway_address;

	int				network_timeout;
	int				network_packet_size;

	static const Configuration* const Get();
	static const Configuration* Load(const std::string &_file);

private:
	static Configuration* configuration;

	Configuration();

	Configuration(const Configuration &_other);
	Configuration & operator=(const Configuration &_other);
};

#endif