/*
 * NeighbourDataBase.h
 *
 *  Created on: 17 Aug 2015
 *      Author: makrai
 */

#ifndef NEIGHBOURDATABASE_H_
#define NEIGHBOURDATABASE_H_

#include "NodeStore.h"
#include "SimplifiedRoadStore.h"

#define NEIGHBOURDATABASE_FORWARD 0
#define NEIGHBOURDATABASE_BACKWARD 1

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
