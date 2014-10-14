#ifdef STATIC_BSP

#ifndef STATIC_OBJECT_BSP_H
#define STATIC_OBJECT_BSP_H

#include <set>
#include <forward_list>

#include <boost\shared_ptr.hpp>

#include "Object.h"

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
	Partition::Partition_Enum partition;

	BSP_Separator(const Partition::Partition_Enum &_partition, const float &_value) : partition(_partition), value(_value) { }
	virtual ~BSP_Separator() { }

	bool operator<(const Vector2 &_point) { return (partition == Partition::VERTICAL ? _point.x < value : _point.y < value); }

private:
	BSP_Separator(const BSP_Separator &_other);
	BSP_Separator& operator=(const BSP_Separator &_other);
};

class BSP_Node
{
public:
	BSP_Node *left = 0, *right = 0;

	BSP_Separator *separator = 0;
	std::forward_list< boost::shared_ptr< Object > > *objects;

	BSP_Node(BSP_Separator *_separator) : separator(_separator) { }
	BSP_Node(std::forward_list< boost::shared_ptr< Object > > *_objects) : objects(_objects) { }
	virtual ~BSP_Node() { }

private:
	BSP_Node(const BSP_Node &_other);
	BSP_Node& operator=(const BSP_Node &_other);
};

class BSP_Tree
{
public:
	BSP_Node *root = 0;

	BSP_Tree(const std::forward_list< boost::shared_ptr< Object > > &_objects);
	virtual ~BSP_Tree();

	std::forward_list< boost::shared_ptr< Object > > * Collision(boost::shared_ptr< Object > _object);

private:
	struct BSP_Line
	{
	public:
		bool sign;
		float value;
		boost::shared_ptr< Object > object;

		mutable std::forward_list< boost::shared_ptr< Object > > objects;

		BSP_Line(const BSP_Line &_other) : sign(_other.sign), value(_other.value), object(_other.object), objects(_other.objects) { }
		BSP_Line(const bool &_sign, const float &_value, boost::shared_ptr< Object > _object) : sign(_sign), value(_value), object(_object) { }
		virtual ~BSP_Line() { };

		bool operator<(const BSP_Line _rhs) const { return value < _rhs.value; }

	private:
		BSP_Line & operator=(const BSP_Line &_other);
	};

	std::set< BSP_Line > * Separate_Objects(const Partition::Partition_Enum &_partition, const std::forward_list< boost::shared_ptr< Object > > &_objects);
	BSP_Node * Split(const Partition::Partition_Enum &_partition, std::set< BSP_Line >::const_iterator _start, std::set< BSP_Line >::const_iterator _end);

	BSP_Tree(const BSP_Tree &_other);
	BSP_Tree& operator=(const BSP_Tree &_other);
};
#endif
#endif