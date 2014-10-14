#include "Object_BSP.h"

#include <iostream>

BSP_Separator::BSP_Separator(SLL< boost::shared_ptr< Object > > *_sll, const Vector2 &_p1, const Vector2& _p2)
{
	// Create the two possible geometrically optimal separation
	int vertical_flag = 0;		float vertical_optimum = (_p1.x + _p2.x) / 2.f;		float best_vertical_cut = _p1.x;	float best_vertical_distance = abs(vertical_optimum - best_vertical_cut);
	int horizontal_flag = 0;	float horizontal_optimum = (_p1.y + _p2.y) / 2.f;	float best_horizontal_cut = _p2.y;	float best_horizontal_distance = abs(horizontal_optimum - best_horizontal_cut);

	// Calculate the object flag for both separation
	SLL_Node< boost::shared_ptr< Object > > *current;
	current = _sll->first;
	while (current)
	{
		if (abs(vertical_optimum - (current->member->center.x - current->member->width)) < best_vertical_distance)
		{ best_vertical_cut = current->member->center.x - current->member->width; best_vertical_distance = abs(vertical_optimum - best_vertical_distance); }
		if (abs(vertical_optimum - (current->member->center.x + current->member->width)) < best_vertical_distance)
		{ best_vertical_cut = current->member->center.x + current->member->width; best_vertical_distance = abs(vertical_optimum - best_vertical_distance); }
		if (abs(vertical_optimum - (current->member->center.y - current->member->height)) < best_horizontal_distance)
		{ best_vertical_cut = current->member->center.y - current->member->height; best_horizontal_distance = abs(vertical_optimum - best_vertical_distance); }
		if (abs(vertical_optimum - (current->member->center.y + current->member->height)) < best_horizontal_distance)
		{ best_vertical_cut = current->member->center.y + current->member->height; best_horizontal_distance = abs(vertical_optimum - best_vertical_distance); }

		current = current->next;
	}

	BSP_Separator vertical = BSP_Separator(Partition::VERTICAL, best_vertical_cut);
	BSP_Separator horizontal = BSP_Separator(Partition::HORIZONTAL, best_horizontal_cut);

	current = _sll->first;
	while (current)
	{
		if (vertical < current->member) vertical_flag--;
		if (vertical > current->member) vertical_flag++;

		if (horizontal < current->member) horizontal_flag--;
		if (horizontal > current->member) horizontal_flag++;
		current = current->next;
	}

	// Select best separation
	if (abs(horizontal_flag) - abs(vertical_flag) < 0)
	{
		type = horizontal.type;
		value = horizontal.value;

		//std::cout << "\t>Separator: y < " << value << " < y" << std::endl;
	}
	else
	{
		type = vertical.type;
		value = vertical.value;

		//std::cout << "\t>Separator: x < " << value << " < x" << std::endl;
	}
}

///

BSP_Node::BSP_Node(SLL< boost::shared_ptr< Object > > *_sll, const Vector2 &_p1, const Vector2& _p2)
{
	if (_sll->count == 1)
	{
		std::cout << ">Only Object [" << _sll->first->member->center.x << ":" << _sll->first->member->center.y << "] bounded!" << std::endl;
		object = _sll->first->member;
	}
	else
	{
		if (_sll->count == 2)
		{
			//std::cout << ">Two Object bounded!" << std::endl;
		}
		else
		{
			//std::cout << ">Working on [" << _p1.x << ":" << _p1.y << "] x [" << _p2.x << ":" << _p2.y << "]" << std::endl;

			// Create optimal separation
			separator = new BSP_Separator(_sll, _p1, _p2);

			// Separate list
			SLL< boost::shared_ptr< Object > > *lesser = _sll->Separate< BSP_Separator >(separator);

			//std::cout << "\t>Original: " << _sll->count << "\tLesser: " << lesser->count << std::endl;

			// Recursive calls
			if (separator->type == Partition::HORIZONTAL)
			{
				if (lesser->count != 0)	left = new BSP_Node(lesser, Vector2(_p1.x, separator->value), _p2);
				if (_sll->count != 0)	right = new BSP_Node(_sll, _p1, Vector2(_p2.x, separator->value));
			}
			else
			{
				if (lesser->count != 0)	left = new BSP_Node(lesser, _p1, Vector2(separator->value, _p2.y));
				if (_sll->count != 0)	right = new BSP_Node(_sll, Vector2(separator->value, _p1.y), _p2);
			}
		}
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

