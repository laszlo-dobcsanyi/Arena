#include "Macro"
#include "Core\Configuration.h"

Configuration* Configuration::configuration = 0;

Configuration::Configuration():
	characters_number(4),

	gateway_address("127.0.0.1"),

	network_timeout(5),
	network_packet_size(512)
{
}

const Configuration* const Configuration::Get()
{
	if (!configuration) configuration = new Configuration();
	assert(configuration);
	return configuration;
}

const Configuration* const Configuration::Load(const std::string &_file)
{
	// TODO do something...
	return Get();
}