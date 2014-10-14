#include "Object_BSP.h"

#include <limits>
#include <iostream>
#include <assert.h>

/*template< class T >
BSP_Separator< T >::BSP_Separator(SLL< T > *_sll, const Vector2 &_p1, const Vector2& _p2)
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
			{ best_vertical_cut = current->member->center.x - current->member->width; best_vertical_distance = abs(vertical_optimum - best_vertical_cut); }
		if (_p1.x < current->member->center.x + current->member->width && current->member->center.x + current->member->width < _p2.x)
			if (abs(vertical_optimum - (current->member->center.x + current->member->width)) < best_vertical_distance)
			{ best_vertical_cut = current->member->center.x + current->member->width; best_vertical_distance = abs(vertical_optimum - best_vertical_cut); }
		if (_p2.y < current->member->center.y - current->member->height && current->member->center.y - current->member->height < _p1.y)
			if (abs(horizontal_optimum - (current->member->center.y - current->member->height)) < best_horizontal_distance)
			{ best_horizontal_cut = current->member->center.y - current->member->height; best_horizontal_distance = abs(horizontal_optimum - best_horizontal_cut); }
		if (_p2.y < current->member->center.y + current->member->height && current->member->center.y + current->member->height < _p1.y)
			if (abs(horizontal_optimum - (current->member->center.y + current->member->height)) < best_horizontal_distance)
			{ best_horizontal_cut = current->member->center.y + current->member->height; best_horizontal_distance = abs(horizontal_optimum - best_horizontal_cut); }

		current = current->next;
	}

	assert(!(best_horizontal_distance == std::numeric_limits<float>::infinity() && best_vertical_distance == std::numeric_limits<float>::infinity()));

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

///

template< class T >
BSP_Node< T >::BSP_Node(SLL< T > *_sll, const Vector2 &_p1, const Vector2& _p2)
{
	if (_sll->count == 1)
	{
		//std::cout << ">Only Object [" << _sll->first->member->center.x << ":" << _sll->first->member->center.y << "] bounded!" << std::endl;
		BSP_Node *current = this;
		current->object = _sll->first->member;

		if (_p1.x < current->object->center.x - current->object->width)
		{
			T object_copy = current->object;
			current->object = 0;
			current->separator = new BSP_Separator(Partition::VERTICAL, object_copy->center.x - object_copy->width);
			current->right = new BSP_Node(object_copy);
			current = current->right;
		}
		if (current->object->center.x + current->object->width < _p2.x)
		{
			T object_copy = current->object;
			current->object = 0;
			current->separator = new BSP_Separator(Partition::VERTICAL, object_copy->center.x + object_copy->width);
			current->left = new BSP_Node(object_copy);
			current = current->left;
		}
		if (_p2.y < current->object->center.y - current->object->height)
		{
			T object_copy = current->object;
			current->object = 0;
			current->separator = new BSP_Separator(Partition::HORIZONTAL, object_copy->center.y - object_copy->height);
			current->right = new BSP_Node(object_copy);
			current = current->right;
		}
		if (current->object->center.y + current->object->height < _p1.y)
		{
			T object_copy = current->object;
			current->object = 0;
			current->separator = new BSP_Separator(Partition::HORIZONTAL, object_copy->center.y + object_copy->height);
			current->left = new BSP_Node(object_copy);
			current = current->left;
		}
	}
	else
	{
		//std::cout << ">Working on [" << _p1.x << ":" << _p1.y << "] x [" << _p2.x << ":" << _p2.y << "]" << std::endl;

		// Create optimal separation
		separator = new BSP_Separator(_sll, _p1, _p2);

		// Separate list
		SLL< T > *lesser = _sll->Separate< BSP_Separator >(separator);

		//std::cout << "\t>Lesser: " << lesser->count << "\tOriginal: " << _sll->count << std::endl;
	}
}

///

template< class T >
BSP_Tree< T >::BSP_Tree(SLL< T > *_objects)
{
	assert(_objects);
	assert(_objects->first);

	// Determine bounding box of the objects;
	Vector2 p1(_objects->first->member->center.x - _objects->first->member->width, _objects->first->member->center.y + _objects->first->member->height);
	Vector2 p2(_objects->first->member->center.x + _objects->first->member->width, _objects->first->member->center.y - _objects->first->member->height);
	
	SLL_Node< T > *current = _objects->first;
	while(current)
	{
		if (current->member->center.x - current->member->width < p1.x) p1.x = current->member->center.x - current->member->width;
		if (p1.y < current->member->center.y + current->member->height) p1.y = current->member->center.y + current->member->height;
		if (p2.x < current->member->center.x + current->member->width) p2.x = current->member->center.x + current->member->width;
		if (current->member->center.y - current->member->height < p2.y) p2.y = current->member->center.y - current->member->height;
	}

	// Create the BSP Tree
	root = new BSP_Node< T >(_objects, p1, p2);
}
*/
