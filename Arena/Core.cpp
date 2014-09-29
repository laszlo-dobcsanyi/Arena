#include "Arena.h"

#define ARENA_UPDATE_INTERVAL 1./60

int main()
{
	Arena* arena = new Arena();
	arena->walls.Add(boost::shared_ptr< Wall >(new Wall(0., 32., 640., 0.)));
	arena->walls.Add(boost::shared_ptr< Wall >(new Wall(0., 640., 32., 32.)));
	arena->heroes.Add(boost::shared_ptr< Hero >(new Hero(Vector2(320., 320.))));

	float elapsed_time = 0.;
	boost::chrono::steady_clock::time_point last_update = boost::chrono::steady_clock::now();
	do
	{
		boost::chrono::steady_clock::time_point now = boost::chrono::steady_clock::now();
		boost::chrono::duration<float> difference = now - last_update;
		elapsed_time += difference.count();
		last_update = now;

		if (ARENA_UPDATE_INTERVAL < elapsed_time)
		{
			arena->Update(elapsed_time);
			elapsed_time = 0.f;
		}
	} while (true);

	return 0;
}