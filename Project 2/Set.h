#ifndef _SET_H
#define _SET_H

#include <string>
using namespace std;
using ItemType = std::string;

class Set
{
public:
	Set();
	~Set();
	Set(const Set& other);
	Set& operator=(const Set& rhs);
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
		Node *next = nullptr;
		Node *prev = nullptr;
	};
	Node* head;
	Node* tail;

	int m_size;
	int howManyGreater(ItemType value) const;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif