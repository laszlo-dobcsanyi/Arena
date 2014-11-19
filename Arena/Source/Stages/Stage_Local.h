#ifndef STAGES_STAGE_LOCAL_H
#define STAGES_STAGE_LOCAL_H

#include "Game\Game_Local.h"
#include "Stages\Stage.h"

class Stage_Local : public Stage, public Game_Local
{
public:
	Stage_Local();

	void Render();

	void Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode);
	void Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode);

	void Dispose();

private:
	Game *game;

	~Stage_Local();

	Stage_Local(const Stage_Local &_other);
	Stage_Local & operator=(const Stage_Local &_other);
};
#endif