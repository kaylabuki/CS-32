#include "Set.h"
#include <iostream>
using namespace std;

Set::Set() 
{
	m_size = 0;
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

bool Set::get(int i, ItemType& value) const
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
	int i = 0;
	while (other.size() > i|| this->size() > i)
	{
		ItemType temp = other.m_array[i];
		other.m_array[i] = m_array[i];
		m_array[i] = temp;
		i++;
	}
	int tempSize = other.m_size;
	other.m_size = m_size;
	m_size = tempSize;
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
