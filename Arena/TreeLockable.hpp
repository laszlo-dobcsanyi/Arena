#ifndef TREE_LOCKABLE_H
#define TREE_LOCKABLE_H

#include <boost\shared_ptr.hpp>

template< class T >
class TreeLockable
{
public:
	T* value;
	TreeLockable< T >* child;
	TreeLockable< T >* next;

	static TreeLockable< T >* base;

	TreeLockable(T* _value) : value(_value), child(0), next(0), base(this) { }

	TreeLockable(T* _value, TreeLockable< T > _tree) : value(_value), child(0), next(0)
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

	~TreeLockable() { };

	TreeLockable< T >* Add(T* _element)
	{
		if (!child)
		{
			child = new Tree(_element);
			return child;
		}
		else
		{
			TreeLockable< T >* current = child;
			while (current->next) { current = current->next; }
			curent->next = new Tree< T >(_element);
			return current->next;
		}
	}

	TreeLockable< T >* Remove(T* _element)
	{
		if (!child) return;

		if (child->value == _element)
		{
			Tree< T >* value = child;
			if (child->child) base->Add(child->child);
			child = child->next;
			return value;
		}

		TreeLockable< T >* previous = child;
		TreeLockable< T >* current = child->next;

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
	TreeLockable(const TreeLockable& _other);
	TreeLockable& operator=(const TreeLockable& _other);
};
#endif