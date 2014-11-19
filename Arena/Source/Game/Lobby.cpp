#include "Macro"

#include "Game\Lobby.h"

Lobby::Lobby()
{
	#ifdef LOGGING
	Logger::Write(LogObject::lobby, LogMask::constructor, "+> Creating Lobby..");
	#endif


	#ifdef LOGGING
	Logger::Write(LogObject::lobby, LogMask::constructor, "<+ Lobby Created!");
	#endif
}

void Lobby::Render()
{

}

void Lobby::Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode)
{

}

void Lobby::Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode)
{

}

void Lobby::Dispose()
{
	if (!disposed) disposed = true;

	#ifdef LOGGING
	Logger::Write(LogObject::lobby, LogMask::dispose, "-> Disposing Lobby..");
	#endif


	#ifdef LOGGING
	Logger::Write(LogObject::lobby, LogMask::dispose, "<- Lobby Disposed!");
	#endif
}

Lobby::~Lobby()
{
	#ifdef LOGGING
	Logger::Write(LogObject::lobby, LogMask::destructor, "-> Destroying Lobby..");
	#endif


	#ifdef LOGGING
	Logger::Write(LogObject::lobby, LogMask::destructor, "<- Lobby Destroyed!");
	#endif
}
