#ifndef GAME_GAME_CLIENT_H
#define GAME_GAME_CLIENT_H

#include <boost\asio.hpp>

#include "Game\Game.h"
#include "Network\Connection.h"

class Connection_Client;

class Game_Client : public Game
{
public:
	Game_Client();
	virtual ~Game_Client();

	void Connect(const boost::asio::ip::tcp::endpoint &_local_endpoint);

	void Update(const float &_elapsed_time);

private:
	boost::asio::io_service io_service;
	boost::thread thread;

	Connection_Client* connection = 0;

	Game_Client(const Game_Client &_other);
	Game_Client & operator=(const Game_Client &_other);
};

#endif