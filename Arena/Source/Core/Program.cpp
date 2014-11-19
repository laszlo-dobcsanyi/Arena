#include "Macro"

#include <assert.h>

#include "Core\Program.h"
#include "Game\Game.h"
#include "Game\Game_Local.h"
#include "Graphics\Graphics.h"
#include "Graphics\Renderer_Game.h"
#include "Graphics\Renderer_Menu.h"
#include "Network\Gateway.h"
#include "Network\Connection.h"

Gateway *Program::gateway = 0;
Connection_Client *Program::connection = 0;
Game_Local *Program::local_game = 0;
Renderer_Menu *Program::menu = 0;

void Program::Create()
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::game, "+> Creating Program..");
	#endif

	//instance->menu = new Renderer_Menu();
	Game_Local *tmp = new Game_Local();
	Program::local_game = tmp;
	glfwSetKeyCallback(Graphics::window, &Program::Handle_Key);
	glfwSetMouseButtonCallback(Graphics::window, &Program::Handle_Mouse);

	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::game, "<+ Program Created!");
	#endif
}

void Program::Destroy()
{
	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::game, "-> Destroying Program..");
	#endif

	if (gateway) gateway->Dispose();
	if (connection) connection->Dispose();
	if (local_game) { Game_Local *tmp = local_game; Program::local_game = 0; tmp->Dispose(); }

	#ifdef LOGGING
	Logger::Write(LogMask::constructor, LogObject::game, "<- Program Destroyed!");
	#endif
}

void Program::Render()
{
	if (gateway) return;
	if (connection) return;
	if (local_game) local_game->Render();
	if (menu) menu->Render();
}

void Program::Handle_Key(GLFWwindow* _window, int _key, int _scancode, int _action, int _mode)
{
	if (gateway) { return; }
	if (connection) { return; }
	if (local_game) { local_game->Handle_Key(_window, _key, _scancode, _action, _mode); return; }
	if (menu) { menu->Handle_Key(_window, _key, _scancode, _action, _mode); return; }
}

void Program::Handle_Mouse(GLFWwindow* _window, int _key, int _action, int _mode)
{
	if (gateway) { return; }
	if (connection) { return; }
	if (local_game) { local_game->Handle_Mouse(_window, _key, _action, _mode); return; }
	if (menu) { menu->Handle_Mouse(_window, _key, _action, _mode); return; }
}