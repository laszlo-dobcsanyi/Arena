#include <boost\chrono.hpp>

#include "Game.h"
#include "Render.h"
#include "MainWindow.h"

#include <boost\foreach.hpp>

#include "Hero.h"
#include "Object_BSP.hpp"

#define UPDATE_INTERVAL 1./30
#define RENDER_INTERVAL 1./30
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

/*
#include <boost\random.hpp>

boost::mt19937 rng;
float float_rng(float min, float max)
{
boost::uniform_real<float> u(min, max);
boost::variate_generator<boost::mt19937&, boost::uniform_real<float> > gen(rng, u);
return gen();
}

//

int tries = 30000;
int hit_count = 1000;
int objects_count = 4;

float width = 128.;
float height = 128.;

//

while (tries--)
{
std::cout << "Generating Objects.." << std::endl;
std::forward_list< boost::shared_ptr< Object > > objects;
for (int i = 0; i < objects_count; ++i)
{
for (int j = 0; j < objects_count; ++j)
{
objects.push_front(boost::shared_ptr< Object >(new Object(Vector2(j * width + width / 2., i * height + height / 2.), float_rng(1., width / 2.), float_rng(1., height / 2.))));
}
}

//std::forward_list< boost::shared_ptr< Object > > objects;
//objects.push_front(boost::shared_ptr< Object >(new Object(Vector2(3.5, 2.5), 3.5, 2.5)));
//objects.push_front(boost::shared_ptr< Object >(new Object(Vector2(8.0, 7.0), 3.0, 2.0)));
//objects.push_front(boost::shared_ptr< Object >(new Object(Vector2(13.0, 7.0), 2.0, 5.0)));
//objects.push_front(boost::shared_ptr< Object >(new Object(Vector2(3.0, 13.0), 2.0, 2.0)));

std::cout << "Generating BSP Tree.." << std::endl;
BSP_Tree tree(objects);
}*/