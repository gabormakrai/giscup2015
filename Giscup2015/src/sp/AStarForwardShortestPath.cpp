/*
 * AStarForwardShortestPath.cpp
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */


#include "AStarForwardShortestPath.h"

AStarForwardShortestPath::AStarForwardShortestPath(int* storage) {
	this->storage = storage;
	this->current = 0;
	this->length = 0.0;
	this->time = 0.0;
}

void AStarForwardShortestPath::init() {
	--current;
}

bool AStarForwardShortestPath::hasNext() {
	return current != -1;
}

int AStarForwardShortestPath::next() {
	int returnValue = storage[current];
	--current;
	return returnValue;
}

void AStarForwardShortestPath::addRoad(int id) {
	storage[current] = id;
	++current;
}
