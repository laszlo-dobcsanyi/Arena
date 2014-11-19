#ifndef CORE_PROGRAM_H
#define CORE_PROGRAM_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

class Gateway;
class Connection_Client;
class Game_Local;
class Renderer_Menu;

class Program
{
public:
	static void Create();
	static void Destroy();

	static void Render();

	static void Handle_Key(GLFWwindow* _window, int _key, int _scancode, int _action, int _mode);
	static void Handle_Mouse(GLFWwindow* _window, int _key, int _action, int _mode);

private:
	static Gateway *gateway;
	static Connection_Client *connection;
	static Game_Local *local_game;
	static Renderer_Menu *menu;

	Program();
	~Program();

	Program(const Program &_other);
	Program & operator=(const Program &_other);
};
#endif