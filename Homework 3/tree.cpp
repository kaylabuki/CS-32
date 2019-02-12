#include <iostream>
using namespace std;

#include <cassert>

// Return the number of ways that all n2 elements of a2 appear
	 // in the n1 element array a1 in the same order (though not
	 // necessarily consecutively).  The empty sequence appears in a
	 // sequence of length n1 in 1 way, even if n1 is 0.
	 // For example, if a1 is the 7 element array
	 //	10 50 40 20 50 40 30
	 // then for this value of a2     the function must return
	 //	10 20 40			1
	 //	10 40 30			2
	 //	20 10 40			0
	 //	50 40 30			3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
	if (n2 == 0)
		return 1;
	if (n1 < n2)
		return 0;
	else if (a2[0] == a1[0])
		return countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1) + countIncludes(a1 + 1, n1 - 1, a2, n2);
	else
		return countIncludes(a1 + 1, n1 - 1, a2, n2);
	return 0;
}

// Exchange two doubles
void exchange(double& x, double& y)
{
	double t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > divider come before all the other elements,
// and all the elements whose value is < divider come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= divider, or n if there is no such element, and firstLess is
// set to the index of the first element that is < divider, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > divider
//   * for firstNotGreater <= i < firstLess, a[i] == divider
//   * for firstLess <= i < n, a[i] < divider
// All the elements > divider end up in no particular order.
// All the elements < divider end up in no particular order.
void divide(double a[], int n, double divider,
	int& firstNotGreater, int& firstLess)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	//  Every element earlier than position firstNotGreater is > divider
	//  Every element from position firstNotGreater to firstUnknown-1 is
	//    == divider
	//  Every element from firstUnknown to firstLess-1 is not known yet
	//  Every element at position firstLess or later is < divider

	firstNotGreater = 0;
	firstLess = n;
	int firstUnknown = 0;
	while (firstUnknown < firstLess)
	{
		if (a[firstUnknown] < divider)
		{
			firstLess--;
			exchange(a[firstUnknown], a[firstLess]);
		}
		else
		{
			if (a[firstUnknown] > divider)
			{
				exchange(a[firstNotGreater], a[firstUnknown]);
				firstNotGreater++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
	int bot = 0;
	int top = n - 1;
	int firstNotGreater = 0;
	int firstLess = 0;
	if (bot < top)
	{
		divide(a, n, a[n / 2], firstNotGreater, firstLess);
		order(a, n - firstLess);
		order(a + firstNotGreater, n - firstNotGreater);
	}
}

int main()
{
	cout << "Testing countIncludes:" << endl;
	double arr1[7] = { 10, 50, 40, 20, 50, 40, 30 };
	double arr2[3] = { 10, 20, 40 };
	double arr3[3] = { 10, 40, 30 };
	double arr4[3] = { 20, 10, 40 }; 
	double arr5[3] = { 50, 40, 30 };
		// then for this value of a2     the function must return
		//	10 20 40			1
		//	10 40 30			2
		//	20 10 40			0
		//	50 40 30			3
	assert(countIncludes(arr1, 7, arr2, 3) == 1);
	cout << "countIncludes Test #1 passed." << endl;
	assert(countIncludes(arr1, 7, arr3, 3) == 2);
	cout << "countIncludes Test #2 passed." << endl;
	assert(countIncludes(arr1, 7, arr4, 3) == 0);
	cout << "countIncludes Test #3 passed." << endl;
	assert(countIncludes(arr1, 7, arr5, 3) == 3);
	cout << "countIncludes Test #4 passed." << endl << endl << "-----------------------------------------------" << endl;

	/////////////////////////////////////////////////////////////////////////////////////////
	cout << "Testing order: " << endl;
	cout << "Test 1:" << endl;
	double arr6[5] = { 5, 1, 4, 2, 3 };
	cout << "Original array: " << endl;
	for (int i = 0; i < 5; i++)
		cout << arr6[i] << " ";
	double tArr6[5] = { 5, 4, 3, 2, 1 };
	cout << endl << "Desired array: " << endl;
	for (int i = 0; i < 5; i++)
		cout << tArr6[i] << " ";
	cout << endl << "Ordering original array..." << endl;
	order(arr6, 5);
	cout << "Comparing arrays:" << endl;
	for (int i = 0; i < 5; i++)
		assert(arr6[i] == tArr6[i]);
	cout << "order Test #1 passed." << endl << endl;
	//--------------------------//
	cout << endl << "Test 2:" << endl;
	double arr7[5] = { -5, -4, -3, -2, -1 };
	cout << "Original array: " << endl;
	for (int i = 0; i < 5; i++)
		cout << arr7[i] << " ";
	double tArr7[5] = { -1, -2, -3, -4, -5 };
	cout << endl << "Desired array: " << endl;
	for (int i = 0; i < 5; i++)
		cout << tArr7[i] << " ";
	cout << endl << "Ordering original array..." << endl;
	order(arr7, 5);
	cout << "Comparing arrays:" << endl;
	for (int i = 0; i < 5; i++)
		assert(arr7[i] == tArr7[i]);
	cout << "order Test #2 passed." << endl << endl;
	//--------------------------//
	cout << endl << "Test 3:" << endl;
	double arr8[5] = { 5, 4, 3, 2, 1 };
	cout << "Original array: " << endl;
	for (int i = 0; i < 5; i++)
		cout << arr8[i] << " ";
	double tArr8[5] = { 5, 4, 3, 2, 1 };
	cout << endl << "Desired array: " << endl;
	for (int i = 0; i < 5; i++)
		cout << tArr8[i] << " ";
	cout << endl << "Ordering original array..." << endl;
	order(arr8, 5);
	cout << "Comparing arrays:" << endl;
	for (int i = 0; i < 5; i++)
		assert(arr8[i] == tArr8[i]);
	cout << "order Test #3 passed." << endl << endl;
}