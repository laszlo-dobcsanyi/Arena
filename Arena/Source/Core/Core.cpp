#include "Macro"

#include <boost\chrono.hpp>

#include "Core\Program.h"
#include "Core\Configuration.h"
#include "Graphics\Graphics.h"

int main()
{
	Graphics::Create();

	Program::Create();

	#ifdef LOGGING
	//Logger::Write_Counters();
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
		if (Configuration::render_interval < elapsed_render_time)
		{
			glfwPollEvents();

			Program::Render();

			glfwSwapBuffers(Graphics::window);

			elapsed_render_time = 0.f;
		}
	} while (!glfwWindowShouldClose(Graphics::window));

	Program::Destroy();

	Graphics::Destroy();
	
	#ifdef LOGGING
	Logger::Write_Counters();
	std::cin.get();
	#endif
	return 0;
}