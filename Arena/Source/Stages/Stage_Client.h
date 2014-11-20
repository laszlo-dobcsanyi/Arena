#ifndef STAGES_STAGE_CLIENT_H
#define STAGES_STAGE_CLIENT_H

#include <boost\asio.hpp>
#include <boost\thread.hpp>

#include "Stages\Stage.h"

class Connection_Client;

class Stage_Client : public Stage
{
public:
	Stage_Client();

	void Render();

	void Handle_Key(GLFWwindow* _window, const int &_key, const int &_scancode, const int &_action, const int &_mode);
	void Handle_Mouse(GLFWwindow* _window, const int &_key, const int &_action, const int &_mode);

	void Dispose();

private:
	boost::thread thread;
	boost::asio::io_service service;
	
	Connection_Client *connection;
	
	~Stage_Client();

	Stage_Client(const Stage_Client &_other);
	Stage_Client & operator=(const Stage_Client &_other);
};
#endif