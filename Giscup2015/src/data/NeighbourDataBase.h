/*
 * NeighbourDataBase.h
 *
 *  Created on: 17 Aug 2015
 *      Author: makrai
 */

#ifndef NEIGHBOURDATABASE_H_
#define NEIGHBOURDATABASE_H_

#include "NodeStore.h"
#include "RoadStore.h"

#define NEIGHBOURDATABASE_FORWARD 0
#define NEIGHBOURDATABASE_BACKWARD 1

class NeighbourDataBase {
public:
	int* count;
	int* id;
	int* offset;
	double* weight;
	int* roadId;
	NeighbourDataBase(NodeStore* nodeStore, RoadStore* roadStore, int mode);
	~NeighbourDataBase();
};

#endif /* NEIGHBOURDATABASE_H_ */
