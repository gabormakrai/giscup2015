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

class NeighbourDataBase {
public:
	int* count;
	int* id;
	int* offset;
	double* weight;
	NeighbourDataBase(NodeStore* nodeStore, RoadStore* roadStore);
	void dispose();
};


#endif /* NEIGHBOURDATABASE_H_ */
