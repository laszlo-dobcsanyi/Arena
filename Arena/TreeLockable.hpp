#ifndef TREE_LOCKABLE_H
#define TREE_LOCKABLE_H

template< class T >
class Tree
{
public:
	Tree< T >* child;
	Tree< T >* next;

	Tree() { };
	~Tree() { };

private:
	Tree(const Tree& _other);
	Tree& operator=(const Tree& _other);

};
#endif