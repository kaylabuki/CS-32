#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

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

	//Testing:
	//get()
	//howManyGreater()
	ItemType x = "x";
	assert(!s.get(2, x) && x == "x");
	assert(s.get(1, x) && x == "c");

	//Testing:
	//unite()
	//subtract()
	Set s1;
	s1.insert("a"), s1.insert("b"), s1.insert("c");
	Set s2;
	s2.insert("b"), s2.insert("c"), s2.insert("d");
	Set s3;
	unite(s1, s2, s3);
	assert(s3.size() == 4 && s3.contains("a") && s3.contains("b") && s3.contains("c") && s3.contains("d"));
	subtract(s1, s2, s3);
	assert(s3.size() == 2 && s3.contains("a") && s3.contains("d"));

}

Set::Set() //DONE
{
	m_size = 0;
	head = nullptr;
	tail = nullptr;
}

Set::~Set() // DONE
{
	if (head != nullptr) //If there's a Set to delete
	{
		Node *nextNode; //Points to the Node after n
		Node *killMe; //Points to the Node we want to delete 

		while (head != nullptr) //While n is not a nullptr
		{
			if (head->next != nullptr) //If the next pointer of n is NOT a nullptr
				nextNode = head->next; //Set nextNode to equal the next pointer of n
			else
				nextNode = nullptr; //If the next pointer of n IS a nullptr, set nextNode to nullptr (stopping while loop)
			killMe = head; //Set killMe to head
			delete killMe; //Delete 
			head = nextNode; //Set head to nextNode
		}
	}
}

Set::Set(const Set& other)
{
	if (other.head == nullptr)
		head = nullptr;
	else
	{
		head = new Node; //Creates a new Node (adress) for the new head pointer
		Node *o = other.head; //Traverses through the "other" Set
		Node *n = head; //Traverses through the new Set

		while (o != nullptr) //While o is pointing to a valid Node
		{
			n->value = o->value; //Set the value of n to the value of o
			if (o->next != nullptr) //If the next Node in o is NOT null
			{
				Node *c = new Node; //Create a new Node for our new Set called c
				n->next = c; //Set n->next to c
				c->prev = n; //Set c->prev to n
			}
			else //If the next Node of o IS null
			{
				n->next = nullptr; //Set the next Node of n to null
				tail = n; //Since this signifies the end of the Set, set the new tail to n
			}
			n = n->next; //Increment n pointer
			o = o->next; // Increment o pointer
		}
	}

	m_size = other.m_size; //Set the size to the size of other
}

Set& Set::operator=(const Set& rhs)
{
	if (&rhs == this) //If the left and right hand sides are the same Set, return this
		return *this;
	else
	{
		Set temp(rhs);
		swap(temp);
	}
	return *this;
}

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
	//Test to see if the value already exists in the set
	if (this->contains(value))
		return false;

	Node *p = new Node; //Create a new Node p to hold new value
	p->value = value; //Set the value of p to the desired value

	//CASE 1: the set contains 0 nodes
	if (head == nullptr)
	{
		head = p;
		tail = p;
	}
	//CASE 2: the set contains 1 or more nodes
	else
	{
		p->next = head;
		head->prev = p;
		head = p;
	}
	m_size++;
	return true;
}

bool Set::erase(const ItemType& value) //DONE
{
	//Test to see if the value exists in the set
	if (!this->contains(value))
		return false;
	
	Node *p = head; //Create pointer to Set to traverse through Set

	while (p != nullptr) //While p does not equal nullptr
	{
		if (p->value == value) //If p points to the Node that contains value
		{
			if (p->next != nullptr) //If the next adress of p is NOT a nullptr
				p->next->prev = p->prev; //Set the prev address of the next Node to the prev address of p
			else //If the next address of p IS a nullptr
				tail = p->prev; //Set the tail to the prev address of p
			if (p->prev != nullptr) //If the prev adress of p is NOT a nullptr
				p->prev->next = p->next; //Set the next address of the prev Node to the next address of p
			else //If the prev address of p IS a nullptr
				head = p->next; //Set the head to the next address of p
			delete p; //Delete p
			m_size--; //Decrement size
			return true; //Return true
		}
		p = p->next; //If p does not equal value, increment p
	}
	return false; //Once we have traversed through the whole Set without finding value, return false
}

bool Set::contains(const ItemType& value) const //DONE
{
	Node *p = head;

	//CASE 1: Set is empty, return false
	if (head == nullptr)
		return false;
	
	//CASE 2: Traverse set to find value, if found return true
	while (p != nullptr)
	{
		if (p->value == value)
			return true;
		p = p->next;
	}

	//CASE 3: Once fully traversed and value is not found, return false
	return false;
}

bool Set::get(int pos, ItemType& value) const //DONE
{ 
	Node *p = head;

	while (p != nullptr)
	{
		if (this->howManyGreater(p->value) == pos)
		{
			value = p->value;
			return true;
		}
		p = p->next;
	}

	return false;
}

void Set::swap(Set& other) //DONE
{
	// swap sizes

	int tempsize = m_size;
	m_size = other.m_size;
	other.m_size = tempsize;

	// swap head pointers

	Node *p = head;
	head = other.head;
	other.head = p;
}

int Set::howManyGreater(ItemType value) const //DONE
{
	Node *p = head;
	int count = 0;

	while (p != nullptr)
	{
		if (value > p->value)
			count++;
		p = p->next;
	}

	return count;
}

void unite(const Set& s1, const Set& s2, Set& result)
{
	ItemType value;
	for(int i = 0; i < s1.size(); i++)
	{
		s1.get(i, value);
		result.insert(value);
	}

	for (int i = 0; i < s2.size(); i++)
	{
		s2.get(i, value);
		result.insert(value);
	}
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
	ItemType value;
	Set common;
	result = common;

	common = s1;
	for (int i = 0; i < s2.size(); i++)
	{
		s2.get(i, value);
		if (common.insert(value))
			result.insert(value);
	}

	common = s2;
	for (int i = 0; i < s1.size(); i++)
	{
		s1.get(i, value);
		if (common.insert(value))
			result.insert(value);
	}
}