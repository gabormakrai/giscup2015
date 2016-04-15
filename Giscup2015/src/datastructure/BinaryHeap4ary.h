/*
 * BinaryHeap4ary.h
 *
 *  Created on: 18 Aug 2015
 *      Author: Gabor Makrai
 *
 */

#ifndef BINARYHEAP4ARY_H_
#define BINARYHEAP4ARY_H_

#include "Heap.h"

/**
 * Class contains a generic binary heap.
 *
 * It is a classic 4-ary binary heap contains a lookup table for finding nodes already in the heap.
 *
 */
template <class T>
class BinaryHeap4ary : public Heap<T> {
public:
	T zeroValue;
	T maxValue;
	int heapSize;
	T* valueArray;
	BinaryHeap4ary(int initialSize, T zeroValue, T maxValue, int* heapLookupTable, int* heapNodeArray, T* heapValueArray);
	~BinaryHeap4ary();
	void init(int sourceNode, T sourceValue);
	int extractMin();
	void decreaseKey(int node, T value);
private:
	void insert(int node, T value);
	void heapify(int i);
	void exchange(int i, int j);
};


#endif /* BINARYHEAP4ARY_H_ */
