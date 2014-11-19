#ifndef STAGES_STAGE_SERVER_H
#define STAGES_STAGE_SERVER_H

#include "Stages\Stage.h"

class Processor;
class Gateway;
class Lobby;
class Game_Server;

class Stage_Server : public Stage
{
public:
	Stage_Server();

	void Render();

	void Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode);
	void Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode);

	void Dispose();

private:
	~Stage_Server();

	Processor *processor;
	Gateway *gateway;
	Lobby *lobby;
	Game_Server *game;

	Stage_Server(const Stage_Server &_other);
	Stage_Server & operator=(const Stage_Server &_other);
};
#endif