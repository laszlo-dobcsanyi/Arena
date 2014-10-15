#ifndef OBJECT_BSP_H
#define OBJECT_BSP_H

#include <list>

#include <boost\shared_ptr.hpp>

#include "Object.h"
#include "ListSeparatable.hpp"

struct Partition
{
public:
	enum Partition_Enum
	{
		VERTICAL,
		HORIZONTAL
	};

private:
	Partition();
};

template< class T >
class BSP_Separator
{
public:
	float value;
	Partition::Partition_Enum type;

	///

	BSP_Separator(const Partition::Partition_Enum &_type, const float &_value) : type(_type), value(_value) { }
	BSP_Separator(SLL< T > *_sll, const Vector2 &_p1, const Vector2& _p2)
	{
		// Create the two possible geometrically optimal separation
		float vertical_optimum = (_p1.x + _p2.x) / 2.f;		float best_vertical_cut = _p1.x;	float best_vertical_distance = std::numeric_limits<float>::infinity();
		float horizontal_optimum = (_p1.y + _p2.y) / 2.f;	float best_horizontal_cut = _p2.y;	float best_horizontal_distance = std::numeric_limits<float>::infinity();

		// Calculate the most optimal separation along the edges
		SLL_Node< T > *current;
		current = _sll->first;
		while (current)
		{
			if (_p1.x < current->member->center.x - current->member->width && current->member->center.x - current->member->width < _p2.x)
			if (abs(vertical_optimum - (current->member->center.x - current->member->width)) < best_vertical_distance)
			{
				best_vertical_cut = current->member->center.x - current->member->width; best_vertical_distance = abs(vertical_optimum - best_vertical_cut);
			}
			if (_p1.x < current->member->center.x + current->member->width && current->member->center.x + current->member->width < _p2.x)
			if (abs(vertical_optimum - (current->member->center.x + current->member->width)) < best_vertical_distance)
			{
				best_vertical_cut = current->member->center.x + current->member->width; best_vertical_distance = abs(vertical_optimum - best_vertical_cut);
			}
			if (_p2.y < current->member->center.y - current->member->height && current->member->center.y - current->member->height < _p1.y)
			if (abs(horizontal_optimum - (current->member->center.y - current->member->height)) < best_horizontal_distance)
			{
				best_horizontal_cut = current->member->center.y - current->member->height; best_horizontal_distance = abs(horizontal_optimum - best_horizontal_cut);
			}
			if (_p2.y < current->member->center.y + current->member->height && current->member->center.y + current->member->height < _p1.y)
			if (abs(horizontal_optimum - (current->member->center.y + current->member->height)) < best_horizontal_distance)
			{
				best_horizontal_cut = current->member->center.y + current->member->height; best_horizontal_distance = abs(horizontal_optimum - best_horizontal_cut);
			}

			current = current->next;
		}

		if (best_horizontal_distance == std::numeric_limits<float>::infinity() && best_vertical_distance == std::numeric_limits<float>::infinity())
		{
			std::cout << "XXX\n";
		}
		//assert(!(best_horizontal_distance == std::numeric_limits<float>::infinity() && best_vertical_distance == std::numeric_limits<float>::infinity()));

		// Select best separation
		if ((best_horizontal_distance < best_vertical_distance && best_horizontal_cut != std::numeric_limits<float>::infinity()) || (best_vertical_cut == std::numeric_limits<float>::infinity()))
		{
			type = Partition::HORIZONTAL;
			value = best_horizontal_cut;

			//std::cout << "\t>Horizontal Separator: y < " << value << " < y" << std::endl;
		}
		else
		{
			type = Partition::VERTICAL;
			value = best_vertical_cut;

			//std::cout << "\t>Vertical Separator: x < " << value << " < x" << std::endl;
		}
	}
	virtual ~BSP_Separator() { }

	///

	bool operator<(T _object)
	{
		return type == Partition::HORIZONTAL ?
			value < _object->center.y - _object->height || value < _object->center.y + _object->height
				:
			value < _object->center.x - _object->width || value < _object->center.x + _object->width;
	}
	bool operator>(T _object)
	{
		return type == Partition::HORIZONTAL ?
			_object->center.y - _object->height < value || _object->center.y + _object->height < value
			:
			_object->center.x - _object->width < value || _object->center.x + _object->width < value;
	}

	///

	bool operator<(const Vector2 _point) { return type == Partition::HORIZONTAL ? value < _point.y : value < _point.x; }
	bool operator>(const Vector2 _point) { return type == Partition::HORIZONTAL ? _point.y < value : _point.x < value; }

private:
	BSP_Separator(const BSP_Separator &_other);
	BSP_Separator & operator=(const BSP_Separator &_other);
};

template< class T >
class BSP_Node
{
public:
	BSP_Node< T > *left = 0, *right = 0;
	BSP_Separator< T > *separator = 0;
	T object = 0;

	BSP_Node< T >(T _object) : object(_object) { };
	BSP_Node< T >(SLL< T > *_sll, const Vector2 &_p1, const Vector2& _p2)
	{
		if (_sll->count == 1)
		{
			std::cout << ">Only Object [" << _sll->first->member->center.x << ":" << _sll->first->member->center.y << "] bounded!" << std::endl;
			BSP_Node *current = this;
			current->object = _sll->first->member;

			if (_p1.x < current->object->center.x - current->object->width)
			{
				T object_copy = current->object;
				current->object = 0;
				current->separator = new BSP_Separator< T >(Partition::VERTICAL, object_copy->center.x - object_copy->width);
				current->right = new BSP_Node(object_copy);
				current = current->right;
			}
			if (current->object->center.x + current->object->width < _p2.x)
			{
				T object_copy = current->object;
				current->object = 0;
				current->separator = new BSP_Separator< T >(Partition::VERTICAL, object_copy->center.x + object_copy->width);
				current->left = new BSP_Node(object_copy);
				current = current->left;
			}
			if (_p2.y < current->object->center.y - current->object->height)
			{
				T object_copy = current->object;
				current->object = 0;
				current->separator = new BSP_Separator< T >(Partition::HORIZONTAL, object_copy->center.y - object_copy->height);
				current->right = new BSP_Node(object_copy);
				current = current->right;
			}
			if (current->object->center.y + current->object->height < _p1.y)
			{
				T object_copy = current->object;
				current->object = 0;
				current->separator = new BSP_Separator< T >(Partition::HORIZONTAL, object_copy->center.y + object_copy->height);
				current->left = new BSP_Node(object_copy);
				current = current->left;
			}
		}
		else
		{
			//std::cout << ">Working on [" << _p1.x << ":" << _p1.y << "] x [" << _p2.x << ":" << _p2.y << "]" << std::endl;

			// Create optimal separation
			separator = new BSP_Separator< T >(_sll, _p1, _p2);

			// Separate list
			SLL< T > *lesser = _sll->Separate< BSP_Separator< T > >(separator);

			//std::cout << "\t>Lesser: " << lesser->count << "\tOriginal: " << _sll->count << std::endl;

			// Recursive calls
			if (lesser->count != 0)	left = new BSP_Node(lesser, separator->type == Partition::HORIZONTAL ? Vector2(_p1.x, separator->value) : _p1, separator->type == Partition::HORIZONTAL ? _p2 : Vector2(separator->value, _p2.y));
			if (_sll->count != 0)	right = new BSP_Node(_sll, separator->type == Partition::HORIZONTAL ? _p1 : Vector2(separator->value, _p1.y), separator->type == Partition::HORIZONTAL ? Vector2(_p2.x, separator->value) : _p2);

			/*if (separator->type == Partition::HORIZONTAL)
			{
			if (lesser->count != 0)	left = new BSP_Node(lesser, Vector2(_p1.x, separator->value), _p2);
			if (_sll->count != 0)	right = new BSP_Node(_sll, _p1, Vector2(_p2.x, separator->value));
			}
			else
			{
			if (lesser->count != 0)	left = new BSP_Node(lesser, _p1, Vector2(separator->value, _p2.y));
			if (_sll->count != 0)	right = new BSP_Node(_sll, Vector2(separator->value, _p1.y), _p2);
			}*/
		}
	}
	virtual ~BSP_Node() { }

private:
	BSP_Node(const BSP_Node &_other);
	BSP_Node & operator=(const BSP_Node &_other);
};

template< class T >
class BSP_Tree
{
public:
	BSP_Node< T > *root = 0;

	BSP_Tree(SLL< T > *_objects)
	{
		assert(_objects);
		assert(_objects->first);

		// Determine bounding box of the objects;
		Vector2 p1(_objects->first->member->center.x - _objects->first->member->width, _objects->first->member->center.y + _objects->first->member->height);
		Vector2 p2(_objects->first->member->center.x + _objects->first->member->width, _objects->first->member->center.y - _objects->first->member->height);

		SLL_Node< T > *current = _objects->first;
		while (current)
		{
			if (current->member->center.x - current->member->width < p1.x) p1.x = current->member->center.x - current->member->width;
			if (p1.y < current->member->center.y + current->member->height) p1.y = current->member->center.y + current->member->height;
			if (p2.x < current->member->center.x + current->member->width) p2.x = current->member->center.x + current->member->width;
			if (current->member->center.y - current->member->height < p2.y) p2.y = current->member->center.y - current->member->height;

			current = current->next;
		}

		// Create the BSP Tree
		root = new BSP_Node< T >(_objects, p1, p2);
	}
	virtual ~BSP_Tree() { }

	T Collision(const Vector2 &_point)
	{
		BSP_Node< T > *current = root;
		while (current)
		{
			if (current->separator)
			{
				if (*(current->separator) < _point) current = current->right;
				else current = current->left;
			}
			else
			{
				assert(current->object);
				return current->object;
			}
		}
		return 0;
	}

private:
	BSP_Tree(const BSP_Tree &_other);
	BSP_Tree & operator=(const BSP_Tree& _other);
};
#endif
