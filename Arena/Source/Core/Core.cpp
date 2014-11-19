#include "Macro"

#include <boost\chrono.hpp>

#include "Core\Configuration.h"
#include "Graphics\Graphics.h"
#include "Stages\Stage_Handler.h"

int main()
{
	Graphics::Create();
	Stage_Handler::Create();

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

			Stage_Handler::Render();

			glfwSwapBuffers(Graphics::window);

			elapsed_render_time = 0.f;
		}
	} while (!glfwWindowShouldClose(Graphics::window));

	Stage_Handler::Destroy();
	Graphics::Destroy();
	
	#ifdef LOGGING
	Logger::Write_Counters();
	std::cin.get();
	#endif
	return 0;
}