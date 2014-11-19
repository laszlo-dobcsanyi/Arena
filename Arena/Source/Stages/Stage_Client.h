#ifndef STAGES_STAGE_CLIENT_H
#define STAGES_STAGE_CLIENT_H

#include "Stages\Stage.h"

class Stage_Client : public Stage
{
public:
	Stage_Client();

	void Render();

	void Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode);
	void Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode);

	void Dispose();

private:
	~Stage_Client();

	Stage_Client(const Stage_Client &_other);
	Stage_Client & operator=(const Stage_Client &_other);
};
#endif