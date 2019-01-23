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
	m_items = old.m_items;
}

Set &Set::operator= (const Set &src)
{
	delete[] m_array;
	m_array = new ItemType[src.m_items];
	for (int i = 0; i < src.m_size; i++)
		m_array[i] = src.m_array[i];
	m_size = src.m_size;
	m_items = src.m_items;
	return *this;
}

Set::~Set()
{
	m_size = 0;
	m_items = 0;
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
	if (m_size == m_items)
		return false;
	for (int i = 0; i < m_size; i++)
	{
		if (m_array[i] == value)
			return false;
	}
	m_array[m_size] = value;
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
		value = this->sort(i);
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

ItemType Set::sort(int index) const
{
	int size = m_size;
	ItemType sorted[DEFAULT_MAX_ITEMS];

	for (int i = 0; i < size; i++)
		sorted[i] = m_array[i];

	for (int i = 0; i < size; i++)
	{
		int minIndex = i;

		for (int j = i; j < size; j++)
			if (sorted[minIndex] > sorted[j])
				minIndex = j;

		ItemType minimum = sorted[minIndex];
		sorted[minIndex] = sorted[i];
		sorted[i] = minimum;
	}

	return sorted[index];
}
