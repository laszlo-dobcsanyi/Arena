#include <boost\chrono.hpp>

#include "Game.h"
#include "Render.h"
#include "MainWindow.h"

#include <boost\random.hpp>
#include <boost\foreach.hpp>

#include "Hero.h"
#include "Object_BSP.h"

#define GAME_UPDATE_INTERVAL 1./60

boost::mt19937 rng;
float float_rng(float min, float max)
{
	boost::uniform_real<float> u(min, max);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);
	return gen();
}

int main()
{
	/*int tries = 30000;
	int hit_count = 1000;
	int objects_count = 64;

	float width = 1280.;
	float height = 900.;

	//

	while (tries--)
	{
		std::cout << "Generating Objects.." << std::endl;
		std::forward_list< boost::shared_ptr< Object > > objects;
		for (int i = 0; i < objects_count; ++i)
		{
			objects.push_front(boost::shared_ptr< Object >(new Object(Vector2(float_rng(0., width), float_rng(0., height)), float_rng(16., 640.), float_rng(16., 256.))));
		}

		//std::forward_list< boost::shared_ptr< Object > > objects;
		//objects.push_front(boost::shared_ptr< Object >(new Object(Vector2(3.5, 2.5), 3.5, 2.5)));
		//objects.push_front(boost::shared_ptr< Object >(new Object(Vector2(8.0, 7.0), 3.0, 2.0)));
		//objects.push_front(boost::shared_ptr< Object >(new Object(Vector2(13.0, 7.0), 2.0, 5.0)));
		//objects.push_front(boost::shared_ptr< Object >(new Object(Vector2(3.0, 13.0), 2.0, 2.0)));

		std::cout << "Generating BSP Tree.." << std::endl;
		BSP_Tree tree(objects);
	}*/

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

	mainWindow->DeleteWindow();
	return 0;
}