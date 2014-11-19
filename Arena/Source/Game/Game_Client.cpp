#include "Macro"

#include <boost\asio.hpp>

#include "Core\Configuration.h"
#include "Game\Game.h"
#include "Game\Arena.h"
#include "Network\Connection.h"

Game_Client::Game_Client() :
	thread(boost::bind(&boost::asio::io_service::run, &io_service))
{
	Connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 6000));
}

Game_Client::~Game_Client()
{

}

void Game_Client::Connect(const boost::asio::ip::tcp::endpoint &_local_endpoint)
{
	connection = new Connection_Client(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 6000));
	connection->Connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(Configuration::gateway_address), Configuration::gateway_port));
}

void Game_Client::Update(const float &_elapsed_time)
{
	arena->Update(_elapsed_time);
}