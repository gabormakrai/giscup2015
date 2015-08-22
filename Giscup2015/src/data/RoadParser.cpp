/*
 * RoadParser.cpp
 *
 *  Created on: 10 Aug 2015
 *      Author: makrai
 */

#include "RoadParser.h"

#include <fstream>
#include <stdlib.h>

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

void RoadParser::loadNodeFile(const char* fileName, unsigned char* buffer, int bufferSize, NodeStore* nodeStore) {

	FILE* source = fopen(fileName, "r");

	int state = 0;

	int var1 = 0;

	char nodeIdChar[32];
	char nodeXChar[32];
	char nodeYChar[32];

	while (!feof(source)) {
		int readedBytes = fread(buffer, 1, bufferSize, source);
		for (int i = 0; i < readedBytes; ++i) {
			if (state == 0 && buffer[i] != ':') {
				nodeIdChar[var1] = buffer[i];
				++var1;
			} else if (state == 0) {
				nodeIdChar[var1] = 0;
				var1 = 0;
				state = 1;
			} else if (state == 1 && buffer[i] == '<') {
				state = 2;
			} else if (state == 2 && buffer[i] == '>') {
				state = 3;
			} else if (state == 3 && buffer[i] == '<') {
				state = 4;
			} else if (state == 4 && buffer[i] == '>') {
				state = 5;
			} else if (state == 5 && buffer[i] != ',') {
				nodeXChar[var1] = buffer[i];
				++var1;
			} else if (state == 5) {
				state = 6;
				nodeXChar[var1] = 0;
				var1 = 0;
			} else if (state == 6 && buffer[i] != ' ') {
				nodeYChar[var1] = buffer[i];
				++var1;
			} else if (state == 6) {
				state = 7;
				nodeYChar[var1] = 0;
			} else if (state == 7 && buffer[i] == 10) {

				int id = atoi(nodeIdChar);

				double x = atof(nodeXChar);

				double y = atof(nodeYChar);

				nodeStore->addNode(id, x, y);
#ifdef _DEBUG_
				cout << "RoadParser: adding new node(id:" << id << ",x:" << x << ",y:" << y << ")" << endl;
#endif
				var1 = 0;
				state = 0;
			}
		}
	}

	fclose(source);

}

void RoadParser::loadRoadFile(const char* fileName, unsigned char* buffer, int bufferSize, RoadStore* roadStore) {

	FILE* source = fopen(fileName, "r");

	int state = 0;

	int var1 = 0;

	char edgeIdChar[32];
	char startNodeIdChar[32];
	char endNodeIdChar[32];
	char lengthChar[32];
	char speedLimitChar[32];

	int positionInFile = 0;
	int currentStart = 0;

	while (!feof(source)) {
		int readedBytes = fread(buffer, 1, bufferSize, source);
		for (int i = 0; i < readedBytes; ++i) {
			if (state == 0 && buffer[i] != ':') {
				edgeIdChar[var1] = buffer[i];
				++var1;
			} else if (state == 0) {
				edgeIdChar[var1] = 0;
				var1 = 0;
				state = 1;
			} else if (state == 1 && buffer[i] != ':') {
				startNodeIdChar[var1] = buffer[i];
				++var1;
			} else if (state == 1) {
				startNodeIdChar[var1] = 0;
				var1 = 0;
				state = 2;
			} else if (state == 2 && buffer[i] != ':') {
				endNodeIdChar[var1] = buffer[i];
				++var1;
			} else if (state == 2) {
				endNodeIdChar[var1] = 0;
				var1 = 0;
				state = 3;
			} else if (state == 3 && buffer[i] != ':') {
				lengthChar[var1] = buffer[i];
				++var1;
			} else if (state == 3) {
				lengthChar[var1] = 0;
				var1 = 0;
				state = 4;
			} else if (state == 4 && buffer[i] != ':') {
				speedLimitChar[var1] = buffer[i];
				++var1;
			} else if (state == 4) {
				speedLimitChar[var1] = 0;
				var1 = 0;
				state = 5;
			} else if (state == 5 && buffer[i] == 10) {
				state = 0;
				var1 = 0;
				int id = atoi(edgeIdChar);
				int startNodeId = atoi(startNodeIdChar);
				int endNodeId = atoi(endNodeIdChar);
				double length = atof(lengthChar);
				double speedLimit = atof(speedLimitChar);
				roadStore->addRoad(id, startNodeId, endNodeId, length, speedLimit, currentStart);
				currentStart = positionInFile;
#ifdef _DEBUG_
				cout << "RoadParser: adding new road(id:" << id << ",startNode:" << startNodeId << ",endNodeId:" << endNodeId << ",length:" << length << ",speedLimit:" << speedLimit << ")" << endl;
#endif
			}
			++positionInFile;
		}
	}

	fclose(source);

}


