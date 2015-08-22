/*
 * ShortestPathWriter.cpp
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */

#include "ShortestPathWriter.h"

#include <fstream>
#include <stdlib.h>

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

void ShortestPathWriter::write(ShortestPath* sp, const char* fileName, const char* roadFile, RoadStore* roadStore, NodeStore* nodeStore, unsigned char* buffer, unsigned char* buffer2, int bufferSize) {

	FILE* source = fopen(roadFile, "r");
	std::ofstream output;
	output.open(fileName);

#ifdef _DEBUG_
	cout << "writing out shortest path..." << endl;
#endif

	for (sp->init(); sp->hasNext();) {

		int pos = 0;
		int road = sp->next();
		int seek = roadStore->positionInFile[road];
		int length = (road + 1) == roadStore->size ? -1 : roadStore->positionInFile[road + 1] - seek;

#ifdef _DEBUG_
		int sNode = roadStore->startNode[road];
		int eNode = roadStore->endNode[road];
		cout << "roadId:" << roadStore->edgeId[road] << " -> " << nodeStore->id[sNode] << " -> " << nodeStore->id[eNode] << endl;
		cout << "seek:" << seek << ", length: " << length << endl;
#endif

		fseek(source, seek, SEEK_SET);

		while (!feof(source)) {
			int readedBytes = fread(buffer, 1, bufferSize, source);
			for (int i = 0; i < readedBytes; ++i) {
				buffer2[pos] = buffer[i];
				++pos;
				if (pos == length) {
					break;
				}
			}
			if (pos == length) {
				break;
			}
		}

		buffer2[pos] = 0;

		output << buffer2;
#ifdef _DEBUG_
		cout << buffer2;
#endif
	}

	output.close();
}
