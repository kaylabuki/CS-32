#include "Set.h"
#include <cassert>
#include <iostream>

int main(){

	// Testing:
	//insert()
	//erase()
	//contains()
	//empty()
	//size()
	Set s;
	assert(!s.erase("a"));
	assert(!s.contains("a"));
	assert(s.size() == 0);
	assert(s.empty());
	assert(s.insert("a"));
	assert(s.size() == 1);
	assert(s.insert("b"));
	assert(s.size() == 2);
	assert(!s.insert("b"));
	assert(s.size() == 2);
	assert(s.insert("c"));
	assert(s.size() == 3);
	assert(!s.erase("d"));
	assert(s.size() == 3);
	assert(s.erase("b"));
	assert(s.size() == 2);
	assert(s.contains("a"));
	assert(!s.contains("b"));
	assert(s.contains("c"));

	cout << "All tests passed";
}

Set::Set() //DONE
{
	m_size = 0;
	head = nullptr;
	tail = nullptr;
}

Set::~Set()
{
	//When a Set is destroyed, the nodes in the linked list must be deallocated.
}

//Set::Set(? ? ? ) //const Set& other
//{
//	//When a brand new Set is created as a copy of an existing Set, enough new nodes must be allocated to hold a duplicate of the original list.
//}

//Set& operator=(? ? ? ) //const Set& rhs
//{
//	When an existing Set(the left - hand side) is assigned the value of another Set(the right - hand side), the result must be that the left - hand side object is a duplicate of the right - hand side object, with no memory leak of list nodes(i.e.no list node from the old value of the left - hand side should be still allocated yet inaccessible).
//}

bool Set::empty() const //DONE
{
	if (this->size() == 0)
		return true;
	return false;
}

int Set::size() const //DONE
{
	return m_size;
}

bool Set::insert(const ItemType& value) //DONE
{
	Node *p;
	
	//Test to see if the value already exists in the set
	p = head;
	while (p != nullptr)
	{
		if (p->value == value)
			return false;
		p = p->next;
	}

	p = new Node;
	p->value = value;
	p->next = head;
	p->prev = nullptr;
	head = p;

	//CASE 1: the set contains 0 nodes
	if (p->next == nullptr)
		tail = p;
	//CASE 2: the set contains 1 or more nodes
	else
		p->next->prev = p;
	m_size++;
	return true;
}

bool Set::erase(const ItemType& value) //DONE
{
	//Test to see if the value exists in the set
	bool found = false;
	Node *p = head;
	while (p != nullptr)
	{
		if (p->value == value)
		{
			found = true;
			break;
		}
		p = p->next;
	}

	if (!found)
		return false;

	//CASE 1: the set contains 0 nodes
	if (head == nullptr)
		return false;

	//CASE 2: the item we want to delete belongs to the first node
	if (head->value == value)
	{
		Node *killMe = head;
		head = killMe->next;
		killMe->next->prev = nullptr;
		delete killMe;
		m_size--;
		return true;
	}

	//CASE 3: the item we want to delete belongs to some other node
	p = head;

	while (p != nullptr)
	{
		if (p->next != nullptr && p->next->value == value)
			break;
		p = p->next;
	}

	if (p != nullptr)
	{
		Node *killMe = p->next;
		p->next = killMe->next;
		p->next->prev = p->prev;
		delete killMe;
		m_size--;
		if (p->next == nullptr) //checks if last node in set and
			tail = p; //adjusts p
	}

	return true;
}

bool Set::contains(const ItemType& value) const //DONE
{
	Node *p = head;

	//CASE 1: Set is empty, return false
	if (head == nullptr)
		return false;

	//CASE 2: Head's value equals value (first in set), return true
	if (head->value == value)
		return true;
	
	//CASE 3: Traverse set to find value, if found return true
	while (p != nullptr)
	{
		if (p->next != nullptr && p->next->value == value)
			return true;
		p = p->next;
	}

	//CASE 4: Once fully traversed and value is not found, return false
	return false;
}

bool Set::get(int pos, ItemType& value) const { return false; }
void Set::swap(Set& other) {}
