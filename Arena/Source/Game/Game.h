#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <boost\asio.hpp>
#include <boost\atomic.hpp>
#include <boost\thread.hpp>

class Arena;
class Game_Local;
class Game_Server;
class Game_Client;
class Gateway;
class Connection_Client;

class Game
{
public:
	Arena *arena = 0;

	virtual void Dispose();

protected:
	boost::atomic< bool > disposed;

	Game();
	virtual ~Game();

	boost::thread updater;

	void Process();
	virtual void Update(const float &_elapsed_time) = 0;

private:
	Game(const Game& _other);
	Game& operator=(const Game&_other);
};

class Game_Server : public Game
{
public:
	Game_Server();
	virtual ~Game_Server();

	void Update(const float &_elapsed_time);

private:
	Gateway* gateway = 0;

	Game_Server(const Game_Server &_other);
	Game_Server operator=(const Game_Server &_other);
};

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