#ifndef CORE_STATE_BUFFER_HPP
#define CORE_STATE_BUFFER_HPP

#include <assert.h>

template< class Base >
class State_Buffer
{
public:
	State_Buffer(const unsigned int &_size, const Base &_first) :
		size(_size),
		current(0),
		next(Next(current))
	{
		assert(0 < _size && "State_Buffer size must be greater than zero!");
		states = new Base[size];// { _first };
		states[current] = _first;
	}

	void Advance()
	{
		next = Next(next);
		current = Next(current);
	}

	Base * Current() { return &states[current]; }
	Base Current_Copy() { return states[current]; }
	Base * Next() { return &states[next]; }
	Base Next_Copy() { return states[next]; }

	~State_Buffer()
	{
		delete states;
	}

private:
	const unsigned int size;

	unsigned int current;
	unsigned int next;

	Base *states;

	unsigned int Next(unsigned int &_value)
	{
		if (size == _value + 1) return 0;
		else return _value + 1;
	}

	State_Buffer(const State_Buffer< Base > &_other);
	State_Buffer & operator=(const State_Buffer< Base > &_other);
};
#endif