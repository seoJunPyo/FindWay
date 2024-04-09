#pragma once
#include "LinkedList.h"
#include "Tile.h"

class Queue : CList<Position>
{
public:
	void enqueue(Position data) { push_front(data); }
	void dequeue() { pop_back(); }
	Position get_back() { return end().get_node()->_Prev->_data; }
	bool isEmpty() const { return _size == 0; }

};