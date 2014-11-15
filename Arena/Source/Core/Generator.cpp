#include "Macro"
#include "Core\Generator.h"

Generator::Generator(const unsigned int &_range) : current(_range)
{
	values = new unsigned int[_range];
	for (unsigned int current = 0; current < _range; ++current)
		values[current] = current;
}

Generator::~Generator()
{
	delete[] values;
}

const unsigned int & Generator::Next()
{
	boost::unique_lock<boost::shared_mutex> lock(mutex);
	if (current == 0)
	{
		#ifdef LOGGING
		Logger::Write(LogMask::fatal_error, LogObject::generator, "# Error @ Generator::Next -> Generator out of range!");
		#endif
		return values[current];
	}

	current--;
	return values[current];
}

void Generator::Return(const unsigned int& _value)
{
	boost::unique_lock<boost::shared_mutex> lock(mutex);
	values[current] = _value;
	current++;
}
