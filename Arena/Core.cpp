#include "Game.h"
#include "MainWindow.h"

#define Game_UPDATE_INTERVAL 1./60

int main()
{
	//MainWindow window;

	Game* game = new Game();
	game->walls.Add(boost::shared_ptr< Wall >(new Wall(0., 32., 640., 0.)));
	//game->walls.Add(boost::shared_ptr< Wall >(new Wall(0., 640., 32., 32.)));
	game->heroes.Add(boost::shared_ptr< Hero >(new Hero(Vector2(640. + 128., 0. - 128.))));
	// case5: 640. + 128., 32. + 128.
	// case6: 0. - 128., 32. + 128.
	// case7: 0. - 128., 0. - 128.
	// case8: 640. + 128., 0. - 128.

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