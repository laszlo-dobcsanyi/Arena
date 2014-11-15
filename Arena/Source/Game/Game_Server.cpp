#include "Macro"

#include "Core\Configuration.h"
#include "Game\Game.h"
#include "Game\Arena.h"
#include "Network\Gateway.h"

Game_Server::Game_Server() :
	gateway(new Gateway(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(Configuration::Get()->gateway_address), Configuration::Get()->gateway_port)))
{

}

Game_Server::~Game_Server()
{

}

void Game_Server::Update(const float &_elapsed_time)
{
	arena->Update(_elapsed_time);
}