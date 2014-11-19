#include "Macro"

#include <assert.h>

#include "Game\Game.h"
#include "Game\Game_Local.h"
#include "Graphics\Graphics.h"
#include "Graphics\Renderer_Menu.h"
#include "Network\Gateway.h"
#include "Network\Connection_Client.h"
#include "Stages\Stage.h"
#include "Stages\Stage_Menu.h"
#include "Stages\Stage_Local.h"
#include "Stages\Stage_Client.h"
#include "Stages\Stage_Server.h"
#include "Stages\Stage_Handler.h"

Stage *Stage_Handler::stage = 0;
boost::shared_mutex Stage_Handler::mutex;

void Stage_Handler::Create()
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::core, "+> Creating Stage_Handler..");
	#endif

	stage = new Stage_Menu();

	glfwSetKeyCallback(Graphics::window, &Stage_Handler::Handle_Key);
	glfwSetMouseButtonCallback(Graphics::window, &Stage_Handler::Handle_Mouse);

	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::core, "<+ Stage_Handler Created!");
	#endif
}

void Stage_Handler::Destroy()
{
	boost::unique_lock<boost::shared_mutex> lock(mutex);

	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::game, "-> Destroying Stage_Handler..");
	#endif
	
	stage->Dispose();
	stage = 0;

	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::game, "<- Stage_Handler Destroyed!");
	#endif
}

void Stage_Handler::Render()
{
	//boost::unique_lock<boost::shared_mutex> lock(mutex);
	stage->Render();

}

void Stage_Handler::Handle_Key(GLFWwindow* _window, int _key, int _scancode, int _action, int _mode)
{
	stage->Handle_Key(_window, _key, _scancode, _action, _mode);

	if (_key == GLFW_KEY_END && _action == GLFW_PRESS) glfwSetWindowShouldClose(_window, GL_TRUE);
}

void Stage_Handler::Handle_Mouse(GLFWwindow* _window, int _key, int _action, int _mode)
{
	stage->Handle_Mouse(_window, _key, _action, _mode);
}

void Stage_Handler::SetStage(const Stages::Type &_stage)
{
	boost::unique_lock<boost::shared_mutex> lock(mutex);

	stage->Dispose();

	switch (_stage)
	{
	case Stages::MENU:
		stage = new Stage_Menu();
		break;
	case Stages::LOCAL:
		//Game_Local *tmp = new Game_Local();
		//local_game = new Game_Local();
		stage = new Stage_Local();
		break;
	case Stages::CLIENT:
		//Program::connection = new Connection_Client();
		stage = new Stage_Client();
		break;
	case Stages::SERVER:
		//gateway = new Gateway(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 0));
		stage = new Stage_Server();
		break;
	}
}