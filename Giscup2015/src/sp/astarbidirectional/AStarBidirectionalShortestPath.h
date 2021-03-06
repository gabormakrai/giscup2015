/*
 * AStarBidirectionalShortestPath.h
 *
 *  Created on: 22 Aug 2015
 *  Author: Gabor Makrai
 */

#ifndef ASTARBIDIRECTIONALSHORTESTPATH_H_
#define ASTARBIDIRECTIONALSHORTESTPATH_H_

#include "../ShortestPath.h"

/**
 *
 * Class for storing the calculated shortest path generated by the bidirectional A* shortest path algorithm
 *
 */
class AStarBidirectionalShortestPath : public ShortestPath {
public:
	// backward
	int* backwardStorage;
	int backwardCurrent;
	int backwardRoads;
	// forward
	int* forwardStorage;
	int forwardCurrent;

	AStarBidirectionalShortestPath(int* backwardStorage, int* forwardStorage);
	bool hasNext();
	int next();
	void addRoad(int id);
	void lastRoadAdded();

	// forward
	void addForwardRoad(int id);
	// backward
	void addBackwardRoad(int id);

};


#endif /* ASTARBIDIRECTIONALSHORTESTPATH_H_ */
