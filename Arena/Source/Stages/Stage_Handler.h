#ifndef STAGES_STAGE_HANDLER_H
#define STAGES_STAGE_HANDLER_H

#include <boost\thread.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>


namespace Stages
{
	enum Type
	{
		NONE,

		MENU,
		LOCAL,
		CLIENT,
		SERVER
	};
}

class Stage;

class Stage_Handler
{
public:
	static void Create();
	static void SetStage(const Stages::Type &_stage);
	static void Destroy();

	static void Render();

	static void Handle_Key(GLFWwindow* _window, int _key, int _scancode, int _action, int _mode);
	static void Handle_Mouse(GLFWwindow* _window, int _key, int _action, int _mode);

private:
	static Stage* stage;
	static boost::shared_mutex mutex;

	Stage_Handler();
};
#endif