/*
 * NodeStore.cpp
 *
 *  Created on: 11 Aug 2015
 *      Author: Gabor Makrai
 */

#include "NodeStore.h"
#include "math.h"

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

// function to calculate distance between two coordinates
double distanceByDistance(double dx, double dy) {
	return sqrt(dx * dx + dy * dy);
}

// function to calculate time distance between two coordinates (assuming the average speed of 11.1m/s, 40km/h)
double distanceByTime(double dx, double dy) {
	return sqrt(dx * dx + dy * dy) / 11.1;
}

NodeStore::NodeStore(int initialStoreSize) {
	x = new double[initialStoreSize];
	y = new double[initialStoreSize];
	id = new int[initialStoreSize];
	size = 0;
	storeSize = initialStoreSize;
	distanceFunction = &distanceByDistance;
}

NodeStore::~NodeStore() {
	delete [] x;
	delete [] y;
	delete [] id;
}

void NodeStore::addNode(int id, double x, double y) {
	if (size == storeSize) {
		int newSize = size * 2;
		double* newX = new double[newSize];
		double* newY = new double[newSize];
		int* newId = new int[newSize];

		for (int i = 0; i < size; ++i) {
			newX[i] = this->x[i];
			newY[i] = this->y[i];
			newId[i] = this->id[i];
		}

		delete [] this->x;
		delete [] this->y;
		delete [] this->id;

		this->x = newX;
		this->y = newY;
		this->id = newId;

		storeSize = newSize;
	}

	this->x[size] = x;
	this->y[size] = y;
	this->id[size] = id;

	++size;
}

void swap(int* id, int j, int i, double* x, double* y) {

#ifdef _DEBUG_
//	cout << "swap -> i: " << i << ", j: " << j << endl;
#endif

	// swap id
    int temp = id[j];
    id[j] = id[i];
    id[i] = temp;
    // swap x
    double temp0 = x[j];
    x[j] = x[i];
    x[i] = temp0;
    // swap y
    temp0 = y[j];
    y[j] = y[i];
    y[i] = temp0;
}

int partition(int* id, int pivot, int left, int right, double* x, double *y) {
    swap(id, pivot, left, x, y);
    pivot = left;
    int i = left + 1;
    for (int j = left + 1; j <= right; j++) {
        if (id[j] < id[pivot]) {
            swap(id, j, i, x, y);
            i++;
        }
    }
    swap(id, pivot, i - 1, x, y);
    return i - 1;
}

int choosePivot(int* id, int left, int right) {
	int aIndex = left;
	int bIndex = (left + right) / 2;
	int cIndex = right;

    int a = id[aIndex];
    int b = id[bIndex];
    int c = id[cIndex];
    int largeIndex, smallIndex;
    if (a > b) {
        largeIndex = aIndex;
        smallIndex = bIndex;
    }
    else {
        largeIndex = bIndex;
        smallIndex = aIndex;
    }
    if (c > id[largeIndex]) {
        return largeIndex;
    }
    else {
        if (c < id[smallIndex]) {
            return smallIndex;
        }
        else {
            return cIndex;
        }
    }
}

void quickSort(int* id, int left, int right, double* x, double* y) {
    if (left >= right) {
        return;
    }
    int pivot = choosePivot(id, left, right);
    pivot = partition(id, pivot, left, right, x, y);
    quickSort(id, left, pivot - 1, x, y);
    quickSort(id, pivot + 1, right, x, y);
}

void NodeStore::sort() {
	quickSort(this->id, 0, this->size - 1, this->x, this->y);
}

int binarySearch(int* id, int first, int last, int element) {
	if (first > last) {
		return -1;
	}

	int index;

	int mid = (first + last) / 2;

	if (element == id[mid]) {
		index = mid;
	} else {
		if (element < id[mid]) {
			index = binarySearch(id, first, mid - 1, element);
		} else {
			index = binarySearch(id, mid + 1, last, element);
		}
	}

	return index;
}

int NodeStore::getIndex(int id) {
	return binarySearch(this->id, 0, this->size - 1, id);
}

void NodeStore::setDistanceFunction(int mode) {
	if (mode == 0) { // distance by distance
		distanceFunction = &distanceByDistance;
	} else { // distance by time
		distanceFunction = &distanceByTime;
	}
}

double NodeStore::distance(int i1, int i2) {
	double dx = x[i1] - x[i2];
	double dy = y[i1] - y[i2];
	return (*distanceFunction)(dx, dy);
}
