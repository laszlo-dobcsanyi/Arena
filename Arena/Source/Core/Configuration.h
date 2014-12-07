#ifndef CORE_CONFIGURATION_H
#define CORE_CONFIGURATION_H

#include <string>

class Configuration
{
public:
	static float			render_interval;

	//

	static float			game_update_interval;

	static unsigned int		hero_state_buffer_size;

	//
	
	static int				window_width;
	static int				window_height;

	static float			camera_min_distance;
	static float			camera_max_distance;
	static float			camera_bottom_limit;
	
	//

	static int				network_timeout;
	static int				network_packet_size;
	static unsigned int		network_processor_threads;
	static unsigned int		network_connections_number;

	static std::string		gateway_address;
	static unsigned int		gateway_port;

	static unsigned int		connection_server_port_offset;

	static std::string		connection_client_server_address;
	static unsigned int		connection_client_server_port;

	//

	static void Load(const std::string &_file);

private:
	Configuration();
};

#endif