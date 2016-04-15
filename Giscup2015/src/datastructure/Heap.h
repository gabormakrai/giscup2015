/*
 * Heap.h
 *
 *  Created on: 18 Aug 2015
 *      Author: Gabor Makrai
 */

#ifndef _HEAP_H_
#define _HEAP_H_

template <class T>
class Heap {
public:
	int size;
	int* lookupTable;
	int* nodeArray;

	virtual ~Heap() { }

	virtual void init(int sourceNode, T sourceValue) = 0;
	virtual int extractMin() = 0;
	virtual void decreaseKey(int node, T value) = 0;
};

#endif /* HEAP_H_ */
