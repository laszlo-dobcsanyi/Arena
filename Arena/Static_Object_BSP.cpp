#ifdef STATIC_BSP
#include "Static_Object_BSP.h"

#include <boost\foreach.hpp>

BSP_Tree::BSP_Tree(const std::forward_list< boost::shared_ptr< Object > > &_objects)
{
	std::set< BSP_Line > *verticals = Separate_Objects(Partition::HORIZONTAL, _objects);
	root = Split(Partition::HORIZONTAL, verticals->cbegin(), --(verticals->cend()));
}

BSP_Tree::~BSP_Tree()
{

}

//

std::set< BSP_Tree::BSP_Line > * BSP_Tree::Separate_Objects(const Partition::Partition_Enum &_partition, const std::forward_list< boost::shared_ptr< Object > > &_objects)
{
	// Split vertically/horizontally into a sorted set
	std::set< BSP_Line > *lines = new std::set< BSP_Line >();
	if (_partition == Partition::HORIZONTAL)
	{
		BOOST_FOREACH(boost::shared_ptr< Object > object, _objects)
		{
			lines->insert(BSP_Line(true, object->center.y - object->height, object));
			lines->insert(BSP_Line(false, object->center.y + object->height, object));
		}
	}
	else
	{
		BOOST_FOREACH(boost::shared_ptr< Object > object, _objects)
		{
			lines->insert(BSP_Line(true, object->center.x - object->width, object));
			lines->insert(BSP_Line(false, object->center.x + object->width, object));
		}
	}

	// Calculate objects of each separate space
	std::forward_list< boost::shared_ptr< Object > > current_objects;
	for (std::set< BSP_Line >::iterator iterator = lines->begin(); iterator != lines->end(); ++iterator)
	{
		if (iterator->sign) current_objects.push_front(iterator->object);
		else current_objects.remove(iterator->object);

		iterator->objects = current_objects;
	}

	return lines;
}

BSP_Node * BSP_Tree::Split(const Partition::Partition_Enum &_partition, std::set< BSP_Line >::const_iterator _start, std::set< BSP_Line >::const_iterator _end)
{
	// Check if this is the bottom of the partition
	if (_start == --_end)
	{
		++_end;

		if (_partition == Partition::HORIZONTAL)
		{
			BSP_Node *node = new BSP_Node(new BSP_Separator(_partition, _end->value));
			std::set< BSP_Line > *verticals = Separate_Objects(Partition::VERTICAL, _start->objects);
			node->left = Split(Partition::VERTICAL, verticals->cbegin(), --(verticals->cend()));
			return node;
		}
		else
		{
			return new BSP_Node(&(_start->objects));
		}
	}

	// Check if there is only two partitions left
	if (_start == --_end)
	{
		++_end;
		if (_partition == Partition::HORIZONTAL)
		{
			BSP_Node *node = new BSP_Node(new BSP_Separator(_partition, _end->value));
			std::set< BSP_Line > *verticals = Separate_Objects(Partition::VERTICAL, _start->objects);
			node->left = Split(Partition::VERTICAL, verticals->cbegin(), --(verticals->cend()));

			verticals = Separate_Objects(Partition::VERTICAL, _end->objects);
			node->right = Split(Partition::VERTICAL, verticals->cbegin(), --(verticals->cend()));
			return node;
		}
		else
		{
			BSP_Node *node = new BSP_Node(new BSP_Separator(_partition, _end->value));
			node->left = new BSP_Node(&(_start->objects));
			node->right = new BSP_Node(&(_end->objects));
			return node;
		}
	}
	++(++_end);

	// Calculate the total wight of this partition and the first middle element
	bool second = false;
	unsigned int total_weights = 0;
	std::set< BSP_Line >::const_iterator middle = _start;
	std::pair< unsigned int, unsigned int > side_weights = std::pair< unsigned int, unsigned int >(0, 0);
	for (std::set< BSP_Line >::const_iterator iterator = _start; iterator != _end; ++iterator)
	{
		if (second) { side_weights.first += std::distance(std::begin(middle->objects), std::end(middle->objects)); middle++; second = false; }
		else { second = true; }

		total_weights += std::distance(std::begin(iterator->objects), std::end(iterator->objects));
	}
	side_weights.second = total_weights - side_weights.first;

	// Calculate the optimal split line
	if (side_weights.first < side_weights.second)
	{
		unsigned int previous_difference;

		// Go to the right as long as we need
		do
		{
			previous_difference = side_weights.second - side_weights.first;

			unsigned int weight = std::distance(std::begin(middle->objects), std::end(middle->objects));
			side_weights.first += weight;
			side_weights.second -= weight;
			++middle;
		} while (side_weights.first < side_weights.second);

		if (previous_difference <= side_weights.first - side_weights.second) --middle;
	}
	else
	{
		if (side_weights.second < side_weights.first)
		{
			unsigned int previous_difference;

			// Go to the left as long as we need
			do
			{
				previous_difference = side_weights.first - side_weights.second;

				--middle;
				unsigned int weight = std::distance(std::begin(middle->objects), std::end(middle->objects));
				side_weights.first -= weight;
				side_weights.second += weight;
			} while (side_weights.second < side_weights.first);

			if (previous_difference < side_weights.second - side_weights.first) ++middle;
		}
	}

	BSP_Node *node = new BSP_Node(new BSP_Separator(_partition, middle->value));
	node->left = Split(_partition, _start, middle);
	node->right = Split(_partition, middle, _end);
	return node;
}

std::forward_list< boost::shared_ptr< Object > > * BSP_Tree::Collision(boost::shared_ptr< Object > _object)
{
	BSP_Node* current = root;
	while (current)
	{
		if (current->separator)
		{
			current = (*current->separator) < _object->updated_center ? current->left : current->right;
		}
		else
		{
			return current->objects;
		}
	}

	return 0;
}
#endif


