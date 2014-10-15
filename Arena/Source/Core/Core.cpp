#define LOGGING
#define UPDATE_INTERVAL 1./50
#define RENDER_INTERVAL 1./50

#include <boost\chrono.hpp>

#include "Source\Macro"
#include "Source\Game\Game.h"
#include "Source\Graphics\Render.h"
#include "Source\Graphics\MainWindow.h"

int main()
{
	MainWindow* mainWindow = MainWindow::GetMainWindow();

	Game *game = Game::Create(Game_Type::LOCAL);

	mainWindow->GetRender()->InitGameRender();

	float elapsed_update_time = 0.;
	float elapsed_render_time = 0.;
	boost::chrono::steady_clock::time_point last_time = boost::chrono::steady_clock::now();
	do
	{
		// Calculate elapsed time
		boost::chrono::steady_clock::time_point now = boost::chrono::steady_clock::now();
		boost::chrono::duration<float> difference = now - last_time;
		elapsed_update_time += difference.count();
		elapsed_render_time += difference.count();
		last_time = now;

		// Update
		if (UPDATE_INTERVAL < elapsed_update_time)
		{
			game->Update(elapsed_update_time);

			elapsed_update_time = 0.f;
		}
		
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
	return 0;
}