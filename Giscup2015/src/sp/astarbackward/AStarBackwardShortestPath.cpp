/*
 * AStarBackwardShortestPath.cpp
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */


#include "AStarBackwardShortestPath.h"

AStarBackwardShortestPath::AStarBackwardShortestPath(int* storage) {
	this->storage = storage;
	this->current = 0;
	this->length = 0.0;
	this->time = 0.0;
	this->roads = 0;
}

void AStarBackwardShortestPath::lastRoadAdded() {
	this->roads = this->current;
	this->current = 0;
}

void AStarBackwardShortestPath::init() {
}

bool AStarBackwardShortestPath::hasNext() {
	return current < roads;
}

int AStarBackwardShortestPath::next() {
	int returnValue = storage[current];
	++current;
	return returnValue;
}

void AStarBackwardShortestPath::addRoad(int id) {
	storage[current] = id;
	++current;
}
