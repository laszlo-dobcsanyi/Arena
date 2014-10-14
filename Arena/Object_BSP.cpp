#include "Object_BSP.h"

#include <limits>
#include <iostream>
#include <assert.h>

BSP_Separator::BSP_Separator(SLL< boost::shared_ptr< Object > > *_sll, const Vector2 &_p1, const Vector2& _p2)
{
	// Create the two possible geometrically optimal separation
	float vertical_optimum = (_p1.x + _p2.x) / 2.f;		float best_vertical_cut = _p1.x;	float best_vertical_distance = std::numeric_limits<float>::infinity();
	float horizontal_optimum = (_p1.y + _p2.y) / 2.f;	float best_horizontal_cut = _p2.y;	float best_horizontal_distance = std::numeric_limits<float>::infinity();

	// Calculate the most optimal separation along the edges
	SLL_Node< boost::shared_ptr< Object > > *current;
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

BSP_Node::BSP_Node(SLL< boost::shared_ptr< Object > > *_sll, const Vector2 &_p1, const Vector2& _p2)
{
	if (_sll->count == 1)
	{
		//std::cout << ">Only Object [" << _sll->first->member->center.x << ":" << _sll->first->member->center.y << "] bounded!" << std::endl;
		BSP_Node *current = this;
		current->object = _sll->first->member;

		if (_p1.x < current->object->center.x - current->object->width)
		{
			boost::shared_ptr< Object > object_copy = current->object;
			current->object = 0;
			current->separator = new BSP_Separator(Partition::VERTICAL, object_copy->center.x - object_copy->width);
			current->right = new BSP_Node(object_copy);
			current = current->right;
		}
		if (current->object->center.x + current->object->width < _p2.x)
		{
			boost::shared_ptr< Object > object_copy = current->object;
			current->object = 0;
			current->separator = new BSP_Separator(Partition::VERTICAL, object_copy->center.x + object_copy->width);
			current->left = new BSP_Node(object_copy);
			current = current->left;
		}
		if (_p2.y < current->object->center.y - current->object->height)
		{
			boost::shared_ptr< Object > object_copy = current->object;
			current->object = 0;
			current->separator = new BSP_Separator(Partition::HORIZONTAL, object_copy->center.y - object_copy->height);
			current->right = new BSP_Node(object_copy);
			current = current->right;
		}
		if (current->object->center.y + current->object->height < _p1.y)
		{
			boost::shared_ptr< Object > object_copy = current->object;
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
		SLL< boost::shared_ptr< Object > > *lesser = _sll->Separate< BSP_Separator >(separator);

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

///

BSP_Tree::BSP_Tree(const std::forward_list< boost::shared_ptr< Object > > &_list)
{
	// Create Separatable list
	SLL< boost::shared_ptr< Object > > *objects = new SLL< boost::shared_ptr< Object > >(_list);

	// Determine bounding box of the objects;
	Vector2 p1((*_list.begin())->center.x - (*_list.begin())->width, (*_list.begin())->center.y + (*_list.begin())->height);
	Vector2 p2((*_list.begin())->center.x + (*_list.begin())->width, (*_list.begin())->center.y - (*_list.begin())->height);
	BOOST_FOREACH(boost::shared_ptr< Object > current, _list)
	{
		if (current->center.x - current->width < p1.x) p1.x = current->center.x - current->width;
		if (p1.y < current->center.y + current->height) p1.y = current->center.y + current->height;
		if (p2.x < current->center.x + current->width) p2.x = current->center.x + current->width;
		if (current->center.y - current->height < p2.y) p2.y = current->center.y - current->height;
	}

	// Create the BSP Tree
	root = new BSP_Node(objects, p1, p2);

	// Release SLL
	delete objects;
}

