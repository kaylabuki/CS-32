#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
	Set s;
	assert(s.empty());
	ItemType z = 9876543;
	assert(!s.get(42, z) && z == 9876543); // x unchanged by get failure
	s.insert(123456789);
	assert(s.size() == 1);
	assert(s.get(0, z) && z == 123456789);

	cout << "Passed all tests" << endl;
}