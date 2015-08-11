/*
 * RoadParser.cpp
 *
 *  Created on: 10 Aug 2015
 *      Author: makrai
 */

#include "RoadParser.h"

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

void RoadParser::loadFile(const char* fileName, unsigned char* buffer, int bufferSize, RoadStore* roadStore) {

	FILE* source = fopen(fileName, "r");

	int state = 0;

	int var1 = 0;

	unsigned char edgeIdChar[32];
	unsigned char startNodeIdChar[32];
	unsigned char endNodeIdChar[32];

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
			} else if (state == 3 && buffer[i] == 10) {
				state = 0;
				var1 = 0;

// TODO: do the conversion...

				roadStore->addRoad(0, 0, 0, 0.0, 0.0);
			}
		}
	}

#ifdef _DEBUG_
	cout << "roadStore->size: " << roadStore->size << endl;
#endif


	fclose(source);

}


