#pragma once
#include <malloc.h>
template <typename T, typename U>
class Heap
{
private:
	struct Node
	{
		T _data;
		U _key;
	};

	Node* CreateNode(T data, U key)
	{
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->_data = data;
		new_node->_key = key;

		return new_node;
	}

	void Swap(int idx1, int idx2)
	{
		Node* temp = _list[idx1];
		_list[idx1] = _list[idx2];
		_list[idx2] = temp;
	}

	int LeftChild(int idx)
	{
		return 2 * idx + 1;
	}

	int RightChild(int idx)
	{
		return 2 * idx + 2;
	}

	int Parent(int idx)
	{
		return (idx - 1) / 2;
	}

public:
	Heap(int capacity = 1000) : _size(0), _capacity(capacity)
	{
		_list = (Node**)malloc(sizeof(Node*) * capacity);
	}

	~Heap()
	{
		for (int i = 0; i < _size; i++)
			free(_list[i]);

		free(_list);
	}

	bool isFull() const
	{
		return _size == _capacity;
	}

	bool isEmpty() const
	{
		return _size == 0;
	}

	int getSize() const
	{
		return _size;
	}

	void reset()
	{
		_size = 0;
	}

	bool Insert(T data, U key)
	{
		if (isFull())
			return false;

		_list[_size++] = CreateNode(data, key);

		int cur = _size - 1;
		int parent = Parent(cur);
		while (_list[parent]->_key > _list[cur]->_key && cur > 0)
		{
			Swap(parent, cur);
			cur = parent;
			parent = Parent(cur);
		}

		return true;
	}

	bool DeleteMin(T* min)
	{
		return Delete(0, min);
	}

	bool Delete(int idx, T * deleted = nullptr)
	{
		if (isEmpty())
			return false;

		if (deleted != nullptr)
			*deleted = _list[idx]->_data;

		Node* target = _list[idx];
		free(target);

		_list[idx] = _list[--_size];


		int cur = idx;
		while (1)
		{
			int selected = 0;
			int left = LeftChild(cur);
			int right = RightChild(cur);

			if (left >= _size)
				break;

			if (right >= _size)
				selected = left;
			else
			{
				if (_list[left]->_key > _list[right]->_key)
					selected = right;
				else
					selected = left;
			}

			if (_list[selected]->_key < _list[cur]->_key)
			{
				Swap(selected, cur);
				cur = selected;
			}
			else
				break;
		}

		return true;


	}

	const T operator[](int idx) const
	{
		return _list[idx]->_data;
	}

private:
	Node** _list;
	int _size;
	int _capacity;
};