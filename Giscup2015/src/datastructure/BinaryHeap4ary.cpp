/*
 * BinaryHeap4ary.cpp
 *
 *  Created on: 18 Aug 2015
 *      Author: Gabor Makrai
 *
 */

#include "BinaryHeap4ary.h"

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

template <class T>
BinaryHeap4ary<T>::BinaryHeap4ary(int initialSize, T zeroValue, T maxValue, int* heapLookupTable, int* heapNodeArray, T* heapValueArray) {
	this->size = 0;
	this->heapSize = initialSize;
	this->lookupTable = heapLookupTable;
	this->nodeArray = heapNodeArray;
	this->valueArray = heapValueArray;
	this->zeroValue = zeroValue;
	this->maxValue = maxValue;
}

template <class T>
BinaryHeap4ary<T>::~BinaryHeap4ary() {
}

template <class T>
void BinaryHeap4ary<T>::init(int sourceNode, T sourceValue) {
    for (int i = 0; i < this->heapSize; ++i) {
    	this->lookupTable[i] = -1;
        this->valueArray[i] = this->maxValue;
        this->nodeArray[i] = -1;
    }

    this->valueArray[0] = sourceValue;
    this->nodeArray[0] = sourceNode;
    this->lookupTable[sourceNode] = 0;
    this->size = 1;
}

template <class T>
int BinaryHeap4ary<T>::extractMin() {
    if (this->size > 0) {
        int minNode = this->nodeArray[0];

        if (this->size > 1) {
            exchange(0, this->size - 1);
            --this->size;
            heapify(0);
        } else {
            --this->size;
            this->nodeArray[0] = -1;
            valueArray[0] = this->maxValue;
        }

        this->lookupTable[minNode] = -1;
        return minNode;
    } else {
        return -1;
    }
}

template <class T>
void BinaryHeap4ary<T>::decreaseKey(int node, T value) {
    if (this->lookupTable[node] == -1) { // insert
        insert(node, this->maxValue);
    }

    int i = this->lookupTable[node];
    this->valueArray[i] = value;
    int parent = (i - 1) / 4;
    while (i > 0 && this->valueArray[parent] > this->valueArray[i]) {
        exchange(i, parent);
        i = parent;
        parent = (i - 1) / 4;
    }
}

template <class T>
void BinaryHeap4ary<T>::insert(int node, T value) {
	this->nodeArray[this->size] = node;
    valueArray[this->size] = value;
    this->lookupTable[node] = this->size;
    heapify(this->size);
    ++this->size;
}

template <class T>
void BinaryHeap4ary<T>::heapify(int i) {
    int c1 = 4 * i + 1;
    int c2 = c1 + 1;
    int c3 = c2 + 1;
    int c4 = c3 + 1;

    int largest = i;
    T largestValue = valueArray[i];
    if (c1 < this->size && valueArray[c1] < largestValue) {
        largest = c1;
        largestValue = valueArray[c1];
    }
    if (c2 < this->size && valueArray[c2] < largestValue) {
    	largest = c2;
        largestValue = valueArray[c2];
    }
    if (c3 < this->size && valueArray[c3] < largestValue) {
    	largest = c3;
        largestValue = valueArray[c3];
    }
    if (c4 < this->size && valueArray[c4] < largestValue) {
    	largest = c4;
        largestValue = valueArray[c4];
    }

    if (largest != i) {
        exchange(i, largest);
        heapify(largest);
    }
}

template <class T>
void BinaryHeap4ary<T>::exchange(int i, int j) {
    int tempLookUp = this->lookupTable[this->nodeArray[i]];
    this->lookupTable[this->nodeArray[i]] = this->lookupTable[this->nodeArray[j]];
    this->lookupTable[this->nodeArray[j]] = tempLookUp;

    int tempNode = this->nodeArray[i];
    this->nodeArray[i] = this->nodeArray[j];
    this->nodeArray[j] = tempNode;

    T tempValue = valueArray[i];
    valueArray[i] = valueArray[j];
    valueArray[j] = tempValue;
}

template class BinaryHeap4ary<double>;
