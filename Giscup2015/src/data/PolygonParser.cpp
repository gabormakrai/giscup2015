/*
 * PolygonParser.cpp
 *
 *  Created on: 22 Aug 2015
 *      Author: makrai
 */

#include "PolygonParser.h"

#include <fstream>
#include <stdlib.h>
#include <cmath>

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

void PolygonParser::parse(const char* fileName, unsigned char* buffer, int bufferSize, PolygonStore* polygonStore) {
	FILE* source = fopen(fileName, "r");

	int state = 0;

	int var1 = 0;
	int var2 = 0;

	char XChar[32];
	char YChar[32];

	double ax = 0.0;
	double ay = 0.0;
	double bx = 0.0;
	double by = 0.0;
	double cx = 0.0;
	double cy = 0.0;

	while (!feof(source)) {
		int readedBytes = fread(buffer, 1, bufferSize, source);
		for (int i = 0; i < readedBytes; ++i) {
			if (state == 0 && buffer[i] != ':') {
				state =1;
			} else if (state == 1 && buffer[i] == '>') {
				state = 2;
			} else if (state == 2 && buffer[i] == '>') {
				state = 3;
			} else if (state == 3 && buffer[i] == '>') {
				state = 4;
			} else if (state == 4 && buffer[i] == '>') {
				state = 5;
			} else if (state == 5 && buffer[i] != ',') {
				XChar[var1] = buffer[i];
				++var1;
			} else if (state == 5) {
				XChar[var1] = 0;
				state = 6;
				var1 = 0;
			} else if (state == 6 && buffer[i] != ' ' && buffer[i] != '<') {
				YChar[var1] = buffer[i];
				++var1;
			} else if (state == 6) {
				YChar[var1] = 0;
				var1 = 0;
				state = 5;

				if (var2 == 0) {
					ax = atof(XChar);
					ay = atof(YChar);
					var2 = 1;
				} else if (var2 == 1) {
					bx = atof(XChar);
					by = atof(YChar);
					var2 = 2;
				} else {
					cx = atof(XChar);
					cy = atof(YChar);

					if (fabs(ax - cx) + fabs(ay - cy) > 0.000001) {
						polygonStore->addPolygon(ax, ay, bx, by, cx, cy);
	#ifdef _PDEBUG_
						cout << "add polygon: ax:" << ax << ",ay:" << ay << ",bx:" << bx << ",by:" << by << ",cx:" << cx << ",cy:" << cy << endl;
						bx = cx;
						by = cy;
	#endif

					}
				}
				if (buffer[i] == '<') {
					state = 10;
				}
			} else if (state == 10 && buffer[i] == 10) {
				var1 = 0;
				var2 = 0;
				state = 0;
			}
		}
	}

	fclose(source);

}

