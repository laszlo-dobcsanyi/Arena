#ifndef TREE_LOCKABLE_H
#define TREE_LOCKABLE_H

#include <boost\shared_ptr.hpp>

template< class T >
class TreeLockable;

template< class T >
class TreeLockable_Node
{
public:
	T* value = 0;
	TreeLockable_Node< T >* child = 0;
	TreeLockable_Node< T >* next = 0;

	TreeLockable_Node(T* _value) : value(_value), child(0), next(0) { };
	~TreeLockable_Node() { };

	TreeLockable_Node< T >* Add(T* _element)
	{
		if (!child)
		{
			child = new TreeLockable_Node(_element);
			return child;
		}
		else
		{
			TreeLockable_Node< T >* current = child;
			while (current->next) { current = current->next; }
			curent->next = new TreeLockable_Node< T >(_element);
			return current->next;
		}
	}

	TreeLockable_Node< T >* Remove(T* _element, TreeLockable< T >* _tree)
	{
		if (!child) return;

		if (child->value == _element)
		{
			TreeLockable_Node< T >* value = child;
			if (child->child) { _tree->base->Add(child->child); }
			child = child->next;
			return value;
		}

		TreeLockable_Node< T >* previous = child;
		TreeLockable_Node< T >* current = child->next;

		while (curent)
		{
			if (current->value == _element)
			{
				if (current->child) { _tree->base->Add(current->child); }
				previous->next = current->next;
				return current;
			}
		}
		return 0;
	}

private:
	TreeLockable_Node(const TreeLockable_Node& _other);
	TreeLockable_Node& operator=(const TreeLockable_Node& _other);
};

template< class T >
class TreeLockable
{
public:
	TreeLockable_Node< T >* base = 0;

	TreeLockable(T* _value) : base(new TreeLockable_Node< T >(_value)) { };
	~TreeLockable() { };

private:
	TreeLockable(const TreeLockable& _other);
	TreeLockable& operator=(const TreeLockable& _other);
};
#endif