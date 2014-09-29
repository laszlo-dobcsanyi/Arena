#include "Game.h"
#include "MainWindow.h"

#define Game_UPDATE_INTERVAL 1./60

int main()
{
	MainWindow window;

	Game* game = new Game();

	float elapsed_time = 0.;
	boost::chrono::steady_clock::time_point last_update = boost::chrono::steady_clock::now();
	do
	{
		boost::chrono::steady_clock::time_point now = boost::chrono::steady_clock::now();
		boost::chrono::duration<float> difference = now - last_update;
		elapsed_time += difference.count();
		last_update = now;

		if (Game_UPDATE_INTERVAL < elapsed_time)
		{
			game->Update(elapsed_time);
			elapsed_time = 0.f;
		}
	} while (true);

	return 0;
}