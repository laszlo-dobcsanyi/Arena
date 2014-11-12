#ifndef CORE_GENERATOR_H
#define CORE_GENERATOR_H

#include <boost\thread.hpp>

class Generator
{
public:
	Generator(const unsigned int &_range);

	const unsigned int & Next();
	void Return(const unsigned int &_value);

private:
	unsigned int current;
	unsigned int* values;
	boost::shared_mutex mutex;

	Generator(const Generator &_other);
	Generator & operator=(const Generator &_other);
};

#endif