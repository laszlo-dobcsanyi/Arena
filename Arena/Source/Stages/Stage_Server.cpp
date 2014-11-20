#include "Macro"

#include "Core\Configuration.h"
#include "Core\Processor.h"
#include "Game\Lobby.h"
#include "Game\Game_Server.h"
#include "Network\Gateway.h"
#include "Stages\Stage_Server.h"

Stage_Server::Stage_Server() :
	Stage(Stages::SERVER),

	gateway(0),
	lobby(0),
	game(0)
{
	processor = new Processor(Configuration::network_processor_threads);
	gateway = new Gateway(processor, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(Configuration::gateway_address), Configuration::gateway_port));
}

void Stage_Server::Render()
{
	if (gateway)
	{
		if (lobby)
		{
			lobby->Render();
		}
		else
		{
			if (game)
			{
				game->Render();
			}
			else
			{
				// TODO
				// We have a gateway, but no lobby/game?
			}
		}
	}
	else
	{
		// TODO
		// Enter gateway IP / show errors
	}
}

void Stage_Server::Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode)
{
	if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS) Stage_Handler::SetStage(Stages::MENU);
}

void Stage_Server::Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode)
{

}


void Stage_Server::Dispose()
{
	if (gateway) gateway->Dispose();
	if (lobby) lobby->Dispose();
	if (game) game->Dispose();
}

Stage_Server::~Stage_Server()
{

}