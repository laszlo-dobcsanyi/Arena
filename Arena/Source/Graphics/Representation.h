#ifndef GRAPHICS_REPRESENTATION_H
#define GRAPHICS_REPRESENTATION_H

template< class Descriptor >
class Representation
{
public:
	virtual void Draw(const Descriptor &_state) = 0;

protected:
	Representation() { }
	~Representation() { }

private:
	Representation(const Representation &_other);
	Representation & operator=(const Representation &_other);
};
#endif