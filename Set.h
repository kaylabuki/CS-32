#ifndef _SET_H
#define _SET_H

#include <string>
using namespace std;
using ItemType = string;

class Set
{
public:
	Set();
	~Set();
	bool empty() const;
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int pos, ItemType& value) const;
	void swap(Set& other);

private:
	struct Node {
		ItemType value;
		Node *next;
		Node *prev;
	};
	Node* head;
	Node* tail;

	int m_size;
};

#endif