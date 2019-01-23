#include "newSet.h"
#include <iostream>
using namespace std;

Set::Set()
{
	m_items = DEFAULT_MAX_ITEMS;
	m_array = new ItemType[DEFAULT_MAX_ITEMS];
	m_size = 0;
}

Set::Set(ItemType items)
{
	m_items = items;
	m_array = new ItemType[items];
	m_size = 0;
}

Set::Set(const Set &old)
{
	m_array = new ItemType[old.m_items];
	for (int i = 0; i < old.m_size; i++)
		m_array[i] = old.m_array[i];
	m_size = old.m_size;
}

Set &Set::operator= (const Set &src)
{
	m_array = new ItemType[src.m_items];
	for (int i = 0; i < src.m_size; i++)
		m_array[i] = src.m_array[i];
	m_size = src.m_size;
	return *this;
}

Set::~Set()
{
	m_size = 0;
	delete[] m_array;
}

bool Set::empty() const
{
	if (this->size() == 0)
		return true;
	return false;
}

int Set::size() const
{
	return m_size;
}

bool Set::insert(const ItemType& value)
{
	if (this->size() == DEFAULT_MAX_ITEMS)
		return false;
	for (int i = 0; i < this->size(); i++)
		if (m_array[i] == value)
			return false;
	m_array[this->size()] = value;
	m_size++;
	return true;
}

bool Set::erase(const ItemType& value)
{
	int index = 0;
	bool found = false;
	for (int i = 0; i < this->size(); i++)
	{
		if (m_array[i] == value)
		{
			index = i;
			found = true;
			break;
		}
	}
	if (found)
	{
		for (int i = index; i < this->size() - 1; i++)
		{
			m_array[i] = m_array[i + 1];
		}
		m_size--;
	}
	return found;
}

bool Set::contains(const ItemType& value) const
{
	for (int i = 0; i < this->size(); i++)
		if (m_array[i] == value)
			return true;
	return false;
}

bool Set::get(int i, ItemType& value)
{
	if (i < 0 || i >= this->size())
		return false;
	else
	{
		this->sort();
		value = m_array[i];
		return true;
	}
}

void Set::swap(Set& other)
{
	Set temp;
	temp = *this;
	*this = other;
	other = temp;
}

void Set::sort()
{
	int size = this->size();

	for (int i = 0; i < size; i++)
	{
		int minIndex = i;

		for (int j = i; j < size; j++)
			if (m_array[minIndex] > m_array[j])
				minIndex = j;

		ItemType minimum = m_array[minIndex];
		m_array[minIndex] = m_array[i];
		m_array[i] = minimum;
	}
}
