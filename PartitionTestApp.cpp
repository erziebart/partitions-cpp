// PartitionTestApp.cpp : Defines the entry point for the console application.
//

// checking for memory leaks
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>

//#include "stdafx.h"
#include "partition.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	{
		// normal constructor
		unsigned int arr1[] = { 2,1,2,0,0,1,4,3,4 };
		size_t len1 = sizeof(arr1) / sizeof(unsigned int);
		partition::Partition p1(arr1, len1);
		cout << p1 << endl;
		cout << "Sum = " << p1.sum() << endl;
		cout << "Prod = " << p1.prod() << endl;
		cout << "Min = " << p1.min() << endl;
		cout << "Max = " << p1.max() << endl;

		// copy constructor
		partition::Partition p2(p1);
		cout << p2 << endl;
		cout << "Sum = " << p2.sum() << endl;
		cout << "Prod = " << p2.prod() << endl;
		cout << "Min = " << p2.min() << endl;
		cout << "Max = " << p2.max() << endl;

		// copy assignment
		unsigned int arr2[] = {3,2,1,2};
		size_t len2 = sizeof(arr2) / sizeof(unsigned int);
		partition::Partition p3(arr2, len2);
		p2 = p3;
		cout << p2 << endl;
		cout << "Sum = " << p2.sum() << endl;
		cout << "Prod = " << p2.prod() << endl;
		cout << "Min = " << p2.min() << endl;
		cout << "Max = " << p2.max() << endl;

		// zero partition
		partition::Partition zero;
		cout << zero.isZero() << endl;
		cout << p1.isZero() << endl;
		cout << zero << endl;
		try {
			cout << "Prod = " << zero.prod() << endl;
			cout << "Min = " << zero.min() << endl;
			cout << "Max = " << zero.max() << endl;
		}
		catch (partition::ZeroPartitionException e) {
			cout << e.what() << endl;
		}

		// comparison
		cout << (p1==p2) << (p1==p3) << (p2==p3) << (p1==zero) << (p1==p1) << endl;
		
		// appending
		partition::Partition p4;
		((p4 += 3) += 2) += 1;
		cout << p4 << endl;
		p1 += p4;
		cout << p1 << endl << p1 + p4 << endl;
	}
	// display memory error report
	_CrtDumpMemoryLeaks();

    return 0;
}

