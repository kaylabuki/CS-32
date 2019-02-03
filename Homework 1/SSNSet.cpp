#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet()
	: m_set()
{}
// Create an empty SSN set.

bool SSNSet::add(unsigned long ssn)
{
	return m_set.insert(ssn);
}
// Add an SSN to the SSNSet.  Return true if and only if the SSN
// was actually added.

int SSNSet::size() const
{
	return m_set.size();
}
// Return the number of SSNs in the SSNSet.

void SSNSet::print() const
{
	ItemType value;
	for (int i = 0; i < this->size(); i++)
	{
		m_set.get(i, value);
		cout << value << endl;
	}
}
// Write every SSN in the SSNSet to cout exactly once, one per
// line.  Write no other text.

