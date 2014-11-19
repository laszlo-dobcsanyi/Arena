#include "Macro"

#include "Stages\Stage_Local.h"

Stage_Local::Stage_Local() :
	Stage(Stages::LOCAL)
{
}

void Stage_Local::Render()
{
	Game_Local::Render();
}

void Stage_Local::Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode)
{
	Game_Local::Handle_Key(_window, _key, _scancode, _action, _mode);
}

void Stage_Local::Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode)
{
	Game_Local::Handle_Mouse(_window, _key, _action, _mode);
}


void Stage_Local::Dispose()
{
	Game_Local::Dispose();
}

Stage_Local::~Stage_Local()
{

}