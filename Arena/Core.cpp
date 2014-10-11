#include <boost\chrono.hpp>

#include "Game.h"
#include "Render.h"
#include "MainWindow.h"

#define GAME_UPDATE_INTERVAL 1./60

int main()
{
	Game* game = new Game();

	MainWindow* mainWindow = MainWindow::GetMainWindow();

	float elapsed_time = 0.;
	boost::chrono::steady_clock::time_point last_update = boost::chrono::steady_clock::now();
	do
	{
		boost::chrono::steady_clock::time_point now = boost::chrono::steady_clock::now();
		boost::chrono::duration<float> difference = now - last_update;
		elapsed_time += difference.count();
		last_update = now;

		if (GAME_UPDATE_INTERVAL < elapsed_time)
		{
			game->Update(elapsed_time);
			elapsed_time = 0.f;
		}
		
		//DRAW
		glfwPollEvents();

		mainWindow->GetRender()->Draw();

		glfwSwapBuffers(mainWindow->GetWindow());
	} while (!glfwWindowShouldClose(mainWindow->GetWindow()));

	//MainWindow::DeleteWindow();
	return 0;
}