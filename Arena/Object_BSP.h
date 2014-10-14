#ifndef OBJECT_BSP_H
#define OBJECT_BSP_H

#include <forward_list>

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

class BSP_Separator
{
public:
	float value;
	Partition::Partition_Enum type;

	BSP_Separator(SLL< boost::shared_ptr< Object > > *_sll, const Vector2 &_p1, const Vector2& _p2);
	virtual ~BSP_Separator() { }

	bool operator<(boost::shared_ptr< Object > _object)
	{
		return type == Partition::HORIZONTAL ?
			value <= _object->center.y - _object->height && value <= _object->center.y + _object->height
				:
			value <= _object->center.x - _object->width && value <= _object->center.x + _object->width;
	}
	bool operator>(boost::shared_ptr< Object > _object)
	{
		return type == Partition::HORIZONTAL ?
			_object->center.y - _object->height <= value && _object->center.y + _object->height <= value
			:
			_object->center.x - _object->width <= value && _object->center.x + _object->width <= value;
	}

private:
	BSP_Separator(const BSP_Separator &_other);
	BSP_Separator(const Partition::Partition_Enum &_type, const float &_value) : type(_type), value(_value) { }
	BSP_Separator & operator=(const BSP_Separator &_other);
};

class BSP_Node
{
public:
	BSP_Node *left = 0, *right = 0;
	BSP_Separator *separator = 0;
	boost::shared_ptr< Object > object = 0;

	BSP_Node(SLL< boost::shared_ptr< Object > > *_sll, const Vector2 &_p1, const Vector2& _p2);
	virtual ~BSP_Node() { }

private:
	BSP_Node(const BSP_Node &_other);
	BSP_Node & operator=(const BSP_Node &_other);
};

class BSP_Tree
{
public:
	BSP_Node *root = 0;

	BSP_Tree(const std::forward_list< boost::shared_ptr< Object > > &_list);
	virtual ~BSP_Tree() { }

private:
	BSP_Tree(const BSP_Tree &_other);
	BSP_Tree & operator=(const BSP_Tree& _other);
};
#endif
