/*
 * AStarBidirectionalShortestPath.cpp
 *
 *  Created on: 22 Aug 2015
 *  Author: Gabor Makrai
 */

#include "AStarBidirectionalShortestPath.h"

AStarBidirectionalShortestPath::AStarBidirectionalShortestPath(int* backwardStorage, int* forwardStorage) {
	// sp part
	this->length = 0.0;
	this->time = 0.0;

	// forward part
	this->forwardStorage = forwardStorage;
	this->forwardCurrent = 0;

	// backward part
	this->backwardStorage = backwardStorage;
	this->backwardCurrent = 0;
	this->backwardRoads = 0;
}

void AStarBidirectionalShortestPath::lastRoadAdded() {
	this->backwardRoads = this->backwardCurrent;
	this->backwardCurrent = 0;
}

bool AStarBidirectionalShortestPath::hasNext() {

	// forward first
	if (forwardCurrent != -1) {
		return true;
	}

	// backward second
	return backwardCurrent < backwardRoads;

}

int AStarBidirectionalShortestPath::next() {
	// if forward still has roads
	if (forwardCurrent != -1) {
		int returnValue = forwardStorage[forwardCurrent];
		--forwardCurrent;
		return returnValue;
	} else {
		int returnValue = backwardStorage[backwardCurrent];
		++backwardCurrent;
		return returnValue;
	}
}

void AStarBidirectionalShortestPath::addRoad(int id) {
}

void AStarBidirectionalShortestPath::addForwardRoad(int id) {
	forwardStorage[forwardCurrent] = id;
	++forwardCurrent;
}

void AStarBidirectionalShortestPath::addBackwardRoad(int id) {
	backwardStorage[backwardCurrent] = id;
	++backwardCurrent;
}
