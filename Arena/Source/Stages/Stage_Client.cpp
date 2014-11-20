#include "Macro"

#include <boost\bind.hpp>

#include "Core\Configuration.h"
#include "Network\Connection_Client.h"
#include "Stages\Stage_Client.h"

Stage_Client::Stage_Client() :
	Stage(Stages::CLIENT),

	service()
{
	connection = new Connection_Client(service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 0));
	connection->Connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(Configuration::gateway_address), Configuration::gateway_port));

	thread = boost::thread(boost::bind(&boost::asio::io_service::run, &service));
}

void Stage_Client::Render()
{

}

void Stage_Client::Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode)
{

}

void Stage_Client::Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode)
{

}


void Stage_Client::Dispose()
{
	if (connection) connection->Dispose();
}

Stage_Client::~Stage_Client()
{

}