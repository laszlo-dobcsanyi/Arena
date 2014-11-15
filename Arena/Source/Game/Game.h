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

namespace Game_Type
{
	enum Type
	{
		LOCAL,
		SERVER,
		CLIENT
	};
};

class Game
{
public:
	Arena *arena = 0;

	static Game * Create(const Game_Type::Type &_type);
	static Game * Get();
	static void Destroy();

protected:
	Game();
	virtual ~Game();

	boost::atomic< bool > disposed;
	boost::thread updater;

	void Process();
	virtual void Update(const float &_elapsed_time) = 0;

private:
	static Game *game;

	Game(const Game& _other);
	Game& operator=(const Game&_other);
};

class Game_Local : public Game
{
public:
	Game_Local();
	virtual ~Game_Local();

	void Update(const float &_elapsed_time);

private:
	Game_Local(const Game_Local &_other);
	Game_Local & operator=(const Game_Local &_other);
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