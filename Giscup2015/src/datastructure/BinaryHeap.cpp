/*
 * BinaryHeap.cpp
 *
 *  Created on: 18 Aug 2015
 *      Author: Gabor Makrai
 *
 */

#include "BinaryHeap.h"

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

template <class T>
BinaryHeap<T>::BinaryHeap(int initialSize, T zeroValue, T maxValue, int* heapLookupTable, int* heapNodeArray, T* heapValueArray) {
	this->size = 0;
	this->heapSize = initialSize;
	this->lookupTable = heapLookupTable;
	this->nodeArray = heapNodeArray;
	this->valueArray = heapValueArray;
	this->zeroValue = zeroValue;
	this->maxValue = maxValue;
}

template <class T>
BinaryHeap<T>::~BinaryHeap() {
}

template <class T>
void BinaryHeap<T>::init(int sourceNode, T sourceValue) {
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
int BinaryHeap<T>::extractMin() {
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
void BinaryHeap<T>::decreaseKey(int node, T value) {
    if (this->lookupTable[node] == -1) { // insert
        insert(node, this->maxValue);
    }

    int i = this->lookupTable[node];
    this->valueArray[i] = value;
    int parent = (i - 1) / 2;
    while (i > 0 && this->valueArray[parent] > this->valueArray[i]) {
        exchange(i, parent);
        i = parent;
        parent = (i - 1) / 2;
    }
}

template <class T>
void BinaryHeap<T>::insert(int node, T value) {
    this->nodeArray[this->size] = node;
    valueArray[this->size] = value;
    this->lookupTable[node] = this->size;
    heapify(this->size);
    ++this->size;
}

template <class T>
void BinaryHeap<T>::heapify(int i) {
    int l = 2 * i + 1;
    int r = l + 1;

    int largest = 0;
    if (l < this->size && this->valueArray[l] < this->valueArray[i]) {
        largest = l;
    } else {
        largest = i;
    }

    if (r < this->size && this->valueArray[r] < this->valueArray[largest]) {
        largest = r;
    }

    if (largest != i) {
        exchange(i, largest);
        heapify(largest);
    }
}

template <class T>
void BinaryHeap<T>::exchange(int i, int j) {
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

template class BinaryHeap<double>;
