#ifndef NETWORK_CONNECTION_CLIENT_H
#define NETWORK_CONNECTION_CLIENT_H

#include "Graphics\Renderer.h"
#include "Network\Connection.h"

class Lobby;
class Game_Client;

class Connection_Client : public Connection, public Renderer
{
public:
	Connection_Client(boost::asio::io_service &_io_service, const boost::asio::ip::tcp::endpoint &_local_endpoint);
	virtual ~Connection_Client();

	void Connect(const boost::asio::ip::tcp::endpoint &_remote_endpoint);

	void Process(char *_data, size_t _received);

	void Render();

	void Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode);
	void Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode);

private:
	Lobby *lobby;
	Game_Client *game;

	void Handle_Connect(const boost::system::error_code &_error);

	Connection_Client(const Connection_Client &_other);
	Connection_Client & operator=(const Connection_Client &_other);
};
#endif