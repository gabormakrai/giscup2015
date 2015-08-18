//============================================================================
// Name        : BinaryHeapTestMain.cpp
// Author      : Gabor Makrai
// Version     :
// Copyright   : x
// Description : Hello World in C++, Ansi-style
//============================================================================

#define _DEBUG_

#include <iostream>
using namespace std;

#include <limits>

#include "../src/datastructure/BinaryHeap.h"

int mainBinaryHeapTest() {
	cout << "BinaryHeapTesting<double>..." << endl;
	BinaryHeap<double>* heap = new BinaryHeap<double>(32, 0.0, std::numeric_limits<double>::max());
	heap->init(0, 1.0);
	heap->decreaseKey(3, 10);
	heap->decreaseKey(4, 11);
	heap->decreaseKey(5, 13);
	heap->decreaseKey(6, 5);

	cout << heap->extractMin() << endl;
	cout << heap->extractMin() << endl;
	cout << heap->extractMin() << endl;
	cout << heap->extractMin() << endl;
	cout << heap->extractMin() << endl;
	cout << heap->extractMin() << endl;

	cout << endl;

	heap->init(0, 2.0);
	heap->decreaseKey(3, 10);
	heap->decreaseKey(4, 11);
	heap->decreaseKey(5, 13);
	heap->decreaseKey(6, 5);

	cout << heap->extractMin() << endl;
	cout << heap->extractMin() << endl;
	heap->decreaseKey(5, 2);
	cout << heap->extractMin() << endl;
	cout << heap->extractMin() << endl;
	cout << heap->extractMin() << endl;
	cout << heap->extractMin() << endl;

	return 0;
}

