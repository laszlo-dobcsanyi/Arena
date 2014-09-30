#include "WallBlock.h"

#include <iostream>

#include "Wall.h"

void WallBlock::Finalize()
{
	std::forward_list< boost::shared_ptr< Wall > >::const_iterator current = walls.cbegin();
	std::forward_list< boost::shared_ptr< Wall > >::const_iterator end = walls.cend();
	if (current == end) return;

	Vector2 p1((*current)->center.x - (*current)->width, (*current)->center.y + (*current)->height), p2((*current)->center.x + (*current)->width, (*current)->center.y - (*current)->height);
	
	for (current++; current != end; ++current)
	{
		if ((*current)->center.x - (*current)->width < p1.x)	p1.x = (*current)->center.x - (*current)->width;
		if (p1.y < (*current)->center.y + (*current)->height)	p1.y = (*current)->center.y + (*current)->height;
		if (p2.x < (*current)->center.x + (*current)->width)	p2.x = (*current)->center.x + (*current)->width;
		if ((*current)->center.y - (*current)->height < p2.y)	p2.y = (*current)->center.y - (*current)->height;
	}

	center = Vector2((p2.x - p1.x) / 2.f, (p1.y - p2.y) / 2.f);
	width = center.x - p1.x + 32;
	height = center.y - p2.y + 32;
}