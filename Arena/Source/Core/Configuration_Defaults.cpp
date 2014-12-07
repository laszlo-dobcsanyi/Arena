#include "Macro"

#include "Core\Configuration.h"

float			Configuration::render_interval = 1.f / 50;

//

float			Configuration::game_update_interval = 1.f / 50;

unsigned int	Configuration::hero_state_buffer_size = 4;


//

int				Configuration::window_width = 800;
int				Configuration::window_height = 600;

float			Configuration::camera_min_distance = 0.01f;
float			Configuration::camera_max_distance = 1000.0f;
float			Configuration::camera_bottom_limit = (window_height - 32.0f) / 2.0f;

//

int				Configuration::network_timeout = 5;
int				Configuration::network_packet_size = 512;
unsigned int	Configuration::network_processor_threads = 4;
unsigned int	Configuration::network_connections_number = 4;

std::string		Configuration::gateway_address = "192.168.1.102";
unsigned int	Configuration::gateway_port = 1425;

unsigned int	Configuration::connection_server_port_offset = 40000;

std::string		Configuration::connection_client_server_address = gateway_address;
unsigned int	Configuration::connection_client_server_port = gateway_port;