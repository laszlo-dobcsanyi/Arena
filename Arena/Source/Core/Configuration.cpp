#include "Macro"

#include  <assert.h>

#include "Core\Configuration.h"
#include "Game\Game.h"

Configuration* Configuration::configuration = 0;

Configuration::Configuration()
{

}

const Configuration* const Configuration::Get()
{
	if (!configuration) configuration = new Configuration();
	assert(configuration);
	return configuration;
}

const Configuration* Configuration::Load(const std::string &_file)
{
	if (Game::Get() == 0)
	{
		// TODO do something...
	}
	return Get();
}