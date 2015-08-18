/*
 * BinaryHeap.cpp
 *
 *  Created on: 18 Aug 2015
 *      Author: makrai
 */

#include "BinaryHeap.h"

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

template <class T>
BinaryHeap<T>::BinaryHeap(int initialSize, T zeroValue, T maxValue) {
	this->size = 0;
	this->heapSize = initialSize;
	this->lookupTable = new int[initialSize];
	this->nodeArray = new int[initialSize];
	this->valueArray = new T[initialSize];
	this->zeroValue = zeroValue;
	this->maxValue = maxValue;
}

template <class T>
BinaryHeap<T>::~BinaryHeap() {
	delete [] lookupTable;
	delete [] nodeArray;
	delete [] valueArray;
}

template <class T>
void BinaryHeap<T>::init(int sourceNode) {
    for (int i = 0; i < this->heapSize; ++i) {
    	this->lookupTable[i] = -1;
        this->valueArray[i] = this->maxValue;
        this->nodeArray[i] = -1;
    }

    this->valueArray[0] = this->zeroValue;
    this->nodeArray[0] = sourceNode;
    this->lookupTable[sourceNode] = 0;
    size = 1;
}

template <class T>
int BinaryHeap<T>::extractMin() {
    if (size > 0) {
        int minNode = nodeArray[0];

        if (size > 1) {
            exchange(0, size - 1);
            --size;
            heapify(0);
        } else {
            --size;
            nodeArray[0] = -1;
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
    nodeArray[size] = node;
    valueArray[size] = value;
    lookupTable[node] = size;
    heapify(size);
    ++size;
}

template <class T>
void BinaryHeap<T>::heapify(int i) {
    int l = 2 * i + 1;
    int r = l + 1;

    int largest = 0;
    if (l < size && valueArray[l] < valueArray[i]) {
        largest = l;
    } else {
        largest = i;
    }

    if (r < size && valueArray[r] < valueArray[largest]) {
        largest = r;
    }

    if (largest != i) {
        exchange(i, largest);
        heapify(largest);
    }
}

template <class T>
void BinaryHeap<T>::exchange(int i, int j) {
    int tempLookUp = lookupTable[nodeArray[i]];
    lookupTable[nodeArray[i]] = lookupTable[nodeArray[j]];
    lookupTable[nodeArray[j]] = tempLookUp;

    int tempNode = nodeArray[i];
    nodeArray[i] = nodeArray[j];
    nodeArray[j] = tempNode;

    T tempValue = valueArray[i];
    valueArray[i] = valueArray[j];
    valueArray[j] = tempValue;
}

template class BinaryHeap<double>;
