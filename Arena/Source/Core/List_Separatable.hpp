#ifndef CORE_LIST_SEPARATABLE_HPP
#define CORE_LIST_SEPARATABLE_HPP

#include <list>

#include <boost\foreach.hpp>

template< class T >
class SLL_Node
{
public:
	SLL_Node *prev = 0;
	T member;
	SLL_Node *next = 0;

	SLL_Node(SLL_Node *_prev, const T& _member) : prev(_prev), member(_member) { }
	SLL_Node(const T& _member) : member(_member) { }
	SLL_Node(const T& _member, SLL_Node *_next) : member(_member), next(_next) { }
	SLL_Node(SLL_Node *_prev, const T &_member, SLL_Node *_next) : prev(_prev), member(_member), next(_next) { }
	virtual ~SLL_Node() { delete next; }

private:
	SLL_Node(const SLL_Node &_other);
	SLL_Node & operator=(const SLL_Node &_other);
};

template< class T >
class SLL
{
public:
	unsigned int count = 0;
	SLL_Node< T > *first = 0;
	SLL_Node< T > *last = 0;

	SLL< T >() { }
	SLL< T >(const std::list< T > &_list) { BOOST_FOREACH(T current, _list) { Insert_Last(current); } }
	virtual ~SLL() { }

	SLL_Node< T > * Insert_Last(const T& _member)
	{
		count++;

		if (first)
		{
			last->next = new SLL_Node< T > (last, _member);
			last = last->next;
			return last;
		}
		else
		{
			first = new SLL_Node< T >(_member);
			last = first;
			return last;
		}
	}

	SLL_Node< T > * Insert_Last(SLL_Node< T > *_node)
	{
		count++;

		if (first)
		{
			last->next = _node;
			_node->prev = last;
			last = _node;
			_node->next = 0;
			return last;
		}
		else
		{
			first = _node;
			last = _node;
			_node->prev = 0;
			_node->next = 0;
			return last;
		}
	}

	template< class S >
	SLL< T > * Separate(S *_separator)
	{
		// Allocate the list of the separated elements
		SLL< T > *lesser = new SLL< T >();

		SLL_Node< T > *current = first, *previous = 0;
		while (current)
		{
			if ((*_separator) > current->member)
			{
				if ((*_separator) < current->member)
				{
					// This element is in both lists, so copy to the other
					lesser->Insert_Last(current->member);
					current = current->next;
				}
				else
				{
					// We need to separate this element
					if (current->prev)
					{
						// This is not the first element
						if (current->next)
						{
							// This is an intermediate element
							current->prev->next = current->next;
							current->next->prev = current->prev;
						}
						else
						{
							// This is the last element
							current->prev->next = 0;
							last = current->prev;
						}
					}
					else
					{
						// This is the first element
						if (current->next)
						{
							// This is not the last element
							current->next->prev = 0;
							first = current->next;
						}
						else
						{
							// This is the only element in the list
							first = 0;
							last = 0;
						}
					}

					// Remove from this list
					SLL_Node< T > * current_copy = current;
					current = current->next;
					lesser->Insert_Last(current_copy);
					count--;
				}
			}
			else
			{
				// This element is fine in this list; Nothing to do
				/*if ((*_separator) < current->member)
				{
					// This element is fine in this list; Nothing to do
				}
				else
				{
					// Copy this value to the other list
					lesser->Insert_Last(current->member);
				}*/

				current = current->next;
			}
		}

		return lesser;
	}

private:
	SLL(const SLL< T > &_other);
	SLL & operator=(const SLL< T > &_other);
};
#endif