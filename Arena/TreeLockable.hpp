#ifndef TREE_LOCKABLE_H
#define TREE_LOCKABLE_H

#include <boost\shared_ptr.hpp>

template< class T >
class Tree
{
public:
	T* value;
	Tree< T >* child;
	Tree< T >* next;

	static Tree< T >* base;

	Tree(T* _value) : value(_value), child(0), next(0), base(this) { }

	Tree(T* _value, Tree< T > _tree) : value(_value), child(0), next(0)
	{
		if (!_tree->child)
		{
			_tree->child = this;
		}
		else
		{
			Tree< T >* current = _tree->child;
			while (current->next) { current = current->next; }
			curent->next = new Tree< T >(_element);
		}
	}

	~Tree() { };

	Tree< T >* Add(T* _element)
	{
		if (!child)
		{
			child = new Tree(_element);
			return child;
		}
		else
		{
			Tree< T >* current = child;
			while (current->next) { current = current->next; }
			curent->next = new Tree< T >(_element);
			return current->next;
		}
	}

	Tree< T >* Remove(T* _element)
	{
		if (!child) return;

		if (child->value == _element)
		{
			Tree< T >* value = child;
			if (child->child) base->Add(child->child);
			child = child->next;
			return value;
		}

		Tree< T >* previous = child;
		Tree< T >* current = child->next;

		while (curent)
		{
			if (current->value == _element)
			{
				if (current->child) base->Add(current->child);
				previous->next = current->next;
				return current;
			}
		}
		return 0;
	}

private:
	Tree(const Tree& _other);
	Tree& operator=(const Tree& _other);
};
#endif