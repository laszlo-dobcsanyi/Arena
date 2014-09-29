#ifndef ARENA_H
#define ARENA_H

#include "Object.h"

class Arena : public Object
{
public:
	Arena() : Object(Vector2(0., 0.), 0., 0.) { }
	~Arena() { }

	void Update(const float& _elapsed_time) { }
	void Report() { }

private:
	Arena(const Arena& _other);
	Arena& operator=(const Arena& _other);
};
#endif