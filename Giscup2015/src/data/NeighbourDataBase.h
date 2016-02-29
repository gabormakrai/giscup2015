/*
 * NeighbourDataBase.h
 *
 *  Created on: 17 Aug 2015
 *  	Author: Gabor Makrai
 */

#ifndef NEIGHBOURDATABASE_H_
#define NEIGHBOURDATABASE_H_

#include "NodeStore.h"
#include "SimplifiedRoadStore.h"

#define NEIGHBOURDATABASE_FORWARD 0
#define NEIGHBOURDATABASE_BACKWARD 1

/**
 *
 * NeigbourDataBase gets the graph from SimplifiedRoadStore and turns to graph into useful data.
 * It creates forward and/or backward graphs in the form of neighbour list.
 * Also it calculates the weight for each edge and stores and the class has a changeable reference to time/distance weights
 *
 */
class NeighbourDataBase {
public:
	int* count;
	int* id;
	int* offset;
	double* weight;
	double* distanceWeight;
	double* timeWeight;
	int* roadId;
	NeighbourDataBase(NodeStore* nodeStore, SimplifiedRoadStore* simplifiedRoadStore, int mode, int* bannedNodes);
	~NeighbourDataBase();
	void setWeight(int mode);
};

#endif /* NEIGHBOURDATABASE_H_ */
