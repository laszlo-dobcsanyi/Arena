#define RENDER_INTERVAL 1./50

#include "Macro"

#include <boost\chrono.hpp>

#include "Game\Game.h"
#include "Graphics\Render.h"
#include "Graphics\MainWindow.h"
#include "Network\Gateway.h"

int main()
{
	MainWindow* mainWindow = MainWindow::GetMainWindow();

	Game *game = Game::Create(Game_Type::LOCAL);

	mainWindow->GetRender()->InitGameRender();

	#ifdef LOGGING
	Logger::Write_Counters();
	#endif

	float elapsed_render_time = 0.;
	boost::chrono::steady_clock::time_point last_time = boost::chrono::steady_clock::now();
	do
	{
		// Calculate elapsed time
		boost::chrono::steady_clock::time_point now = boost::chrono::steady_clock::now();
		boost::chrono::duration<float> difference = now - last_time;
		elapsed_render_time += difference.count();
		last_time = now;
		
		// Render
		if (RENDER_INTERVAL < elapsed_render_time)
		{
			glfwPollEvents();

			mainWindow->GetRender()->Draw();

			glfwSwapBuffers(mainWindow->GetWindow());

			elapsed_render_time = 0.f;
		}
	} while (!glfwWindowShouldClose(mainWindow->GetWindow()));

	mainWindow->DeleteWindow();
	game->Destroy();
	
	#ifdef LOGGING
	Logger::Write_Counters();
	std::cin.get();
	#endif
	return 0;
}