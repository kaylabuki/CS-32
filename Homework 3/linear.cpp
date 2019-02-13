#include <cassert>
#include <iostream>
using namespace std;

// somePredicate function, DONE
bool somePredicate(double x)
{
	return x < 0;
}

// Return true if the somePredicate function returns true for at
	  // least one of the array elements, false otherwise. DONE
bool anyTrue(const double a[], int n) //DONE
{
	if (n == 0)
		return false;
	else if (somePredicate(a[0]))
		return true;
	else
		return anyTrue(a + 1, n - 1);
}

// Return the number of elements in the array for which the
// somePredicate function returns true. DONE
int countTrue(const double a[], int n)
{
	if (n == 0)
		return n;
	else if (somePredicate(a[0]))
		return 1 + countTrue(a + 1, n - 1);
	else
		return countTrue(a + 1, n - 1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1. DONE
int firstTrue(const double a[], int n)
{
	if (n == 0)
		return -1;
	else if (somePredicate(a[0]))
		return 0;
	else
	{
		int result = firstTrue(a + 1, n - 1);
		if (result != -1)
			return 1 + result;
		else
			return result;
	}
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no 
// elements, return -1. DONE
int positionOfMin(const double a[], int n)
{
	if (n == 0)
		return -1;
	if (n == 1)
		return 0;
	int pos = positionOfMin(a + 1, n - 1);
	if (a[0] < a[pos + 1])
		return 0;
	else
		return 1 + pos;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
// DONE
bool includes(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 == 0)
		return true;
	if (n1 < n2)
		return false;
	else if (a2[0] == a1[0])
		return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	else
		return includes(a1 + 1, n1 - 1, a2, n2);
	return false;
}

int main()
{
	double arr1[5] = { 1, 2, 3, 4, 5 };
	double arr2[5] = { 1, -2, 3, -4, 5 };
	double arr3[5] = { -1, -2, -3, -4, -5 };
	double arr4[1] = { 1 };

	assert(!anyTrue(arr1, 5));
	assert(anyTrue(arr2, 5));
	assert(anyTrue(arr3, 5));
	assert(!anyTrue(arr1, 0));
	assert(!anyTrue(arr2, 1));
	assert(anyTrue(arr3, 1));
	assert(!anyTrue(arr4, 1));

	assert(countTrue(arr1, 5) == 0);
	assert(countTrue(arr2, 5) == 2);
	assert(countTrue(arr3, 5) == 5);
	assert(countTrue(arr3, 0) == 0);
	assert(countTrue(arr3, 1) == 1);
	assert(countTrue(arr4, 1) == 0);

	assert(firstTrue(arr1, 5) == -1);
	assert(firstTrue(arr2, 5) == 1);
	assert(firstTrue(arr2 + 1, 4) == 0);
	assert(firstTrue(arr3, 5) == 0);
	assert(firstTrue(arr4, 1) == -1);

	assert(positionOfMin(arr1, 5) == 0);
	assert(positionOfMin(arr2, 5) == 3);
	assert(positionOfMin(arr3, 5) == 4);
	assert(positionOfMin(arr3, 4) == 3);
	assert(positionOfMin(arr4, 1) == 0);

	double arr5[7] = { 10, 50, 40, 20, 50, 40, 30 };
	double arr6[3] = { 50, 20, 30 }; 
	double arr7[3] = { 50, 40, 40 };
	double arr8[3] = { 50, 30, 20 };
	double arr9[3] = { 10, 20, 20 };
	
	assert(includes(arr5, 7, arr6, 3));
	assert(includes(arr5, 7, arr7, 3));
	assert(!includes(arr5, 7, arr8, 3));
	assert(!includes(arr5, 7, arr9, 3));

	cout << "All tests passed";
}