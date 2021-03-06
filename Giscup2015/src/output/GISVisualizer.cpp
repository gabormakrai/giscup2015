/*
 * GISVisualizer.cpp
 *
 *  Created on: 20 Aug 2015
 *  Author: Gabor Makrai
 */

#include "GISVisualizer.h"
#include <fstream>
#include <iomanip>
#include <stdlib.h>

#include <iostream>

void GISVisualizer::writeGISFiles(const char* nodeFile, const char* roadFile, const char* polygonNodeFile, const char* polygonFile, NodeStore* nodeStore, RoadStore* roadStore, PolygonStore* polygonStore, int* bannedNodes) {

	double* xNoise = new double[nodeStore->size];
	double* yNoise = new double[nodeStore->size];

	srand(42);

	for (int i = 0; i < nodeStore->size; ++i) {
		double noise = ((double)rand() / (RAND_MAX)) * 2.0 * NOISE_LEVEL - NOISE_LEVEL;
		xNoise[i] = noise;
		noise = ((double)rand() / (RAND_MAX)) * 2.0 * NOISE_LEVEL - NOISE_LEVEL;
		yNoise[i] = noise;
	}

	std::fstream fs;
	fs.open(nodeFile, std::fstream::out);

	fs << "id,x,y" << std::endl;

	for (int i = 0; i < nodeStore->size; ++i) {
		fs << std::setprecision(16) << nodeStore->id[i] << "," << nodeStore->x[i]+xNoise[i] << "," << nodeStore->y[i]+yNoise[i] << std::endl;
	}

	fs.close();

	fs.open(roadFile, std::fstream::out);

	fs << "id;linestring" << std::endl;

	for (int i = 0; i < roadStore->size; ++i) {
		double x1 = nodeStore->x[roadStore->startNode[i]] + xNoise[roadStore->startNode[i]];
		double y1 = nodeStore->y[roadStore->startNode[i]] + yNoise[roadStore->startNode[i]];
		double x2 = nodeStore->x[roadStore->endNode[i]] + xNoise[roadStore->endNode[i]];
		double y2 = nodeStore->y[roadStore->endNode[i]] + yNoise[roadStore->endNode[i]];
		fs << std::setprecision(16) << roadStore->roadId[i] << ";LINESTRING(" << x1 << " " << y1 << "," << x2 << " " << y2 << ")" << std::endl;
	}

	fs.close();

	fs.open(polygonFile, std::fstream::out);
	int polygonId = 0;

	fs << "id;linestring" << std::endl;
	for (int i = 0; i < polygonStore->size; ++i) {

		double ax = polygonStore->ax[i];
		double ay = polygonStore->ay[i];
		double bx = polygonStore->bx[i];
		double by = polygonStore->by[i];
		double cx = polygonStore->cx[i];
		double cy = polygonStore->cy[i];

		fs << std::setprecision(16) << (polygonId++) << ";LINESTRING(" << ax << " " << ay << "," << bx << " " << by << ")" << std::endl;
		fs << std::setprecision(16) << (polygonId++) << ";LINESTRING(" << bx << " " << by << "," << cx << " " << cy << ")" << std::endl;
		fs << std::setprecision(16) << (polygonId++) << ";LINESTRING(" << cx << " " << cy << "," << ax << " " << ay << ")" << std::endl;

	}

	fs.close();

	fs.open(polygonNodeFile, std::fstream::out);
	fs << "id,x,y" << std::endl;

	for (int i = 0; i < nodeStore->size; ++i) {
		if (bannedNodes[i] == 1) {
			fs << std::setprecision(16) << nodeStore->id[i] << "," << nodeStore->x[i]+xNoise[i] << "," << nodeStore->y[i]+yNoise[i] << std::endl;
		}
	}

	fs.close();
}

void GISVisualizer::writeAStarBinaryHeap(const char* heapNodeFile, const char* closedNodeFile, const char* shortestPathFile, AStarForwardBinaryHeap* algo) {

	int from = algo->from;
	int to = algo->to;

	NodeStore* nodeStore = algo->nodeStore;

	// do the heapFile
	std::fstream fs;
	fs.open(heapNodeFile, std::fstream::out);
	fs << "id,x,y" << std::endl;

	for (int i = 0; i < algo->heap->size; ++i) {
		int node = algo->heap->nodeArray[i];

		fs << std::setprecision(16) << node << "," << nodeStore->x[node] << "," << nodeStore->y[node] << std::endl;

	}
	fs.close();

	// do the closedFile
	fs.open(closedNodeFile, std::fstream::out);
	fs << "id,x,y" << std::endl;

	for (int i = 0; i < nodeStore->size; ++i) {
		if (algo->closed[i] == 1) {
			int node = i;
			fs << std::setprecision(16) << node << "," << nodeStore->x[node] << "," << nodeStore->y[node] << std::endl;
		}
	}
	fs.close();

	// do the shortestPath
	fs.open(shortestPathFile, std::fstream::out);
	fs << "id,linestring" << std::endl;

	int current = to;
	int previous = algo->previous[current];
	int edgeId = 0;

	while (true) {

		double x1 = nodeStore->x[previous];
		double y1 = nodeStore->y[previous];
		double x2 = nodeStore->x[current];
		double y2 = nodeStore->y[current];

		previous = current;
		current = algo->previous[current];

		fs << std::setprecision(16) << (edgeId++) << ";LINESTRING(" << x1 << " " << y1 << "," << x2 << " " << y2 << ")" << std::endl;

		if (current == from) {
			break;
		}
	}

	fs.close();

}

void GISVisualizer::writeAStarBinaryHeap(const char* heapNodeFile, const char* closedNodeFile, const char* shortestPathFile, AStarBackwardBinaryHeap* algo) {

	int from = algo->from;
	int to = algo->to;

	NodeStore* nodeStore = algo->nodeStore;

	// do the heapFile
	std::fstream fs;
	fs.open(heapNodeFile, std::fstream::out);
	fs << "id,x,y" << std::endl;

	BinaryHeap<double>* heap = algo->heap;
	for (int i = 0; i < heap->size; ++i) {
		int node = heap->nodeArray[i];

		fs << std::setprecision(16) << node << "," << nodeStore->x[node] << "," << nodeStore->y[node] << std::endl;

	}
	fs.close();

	// do the closedFile
	fs.open(closedNodeFile, std::fstream::out);
	fs << "id,x,y" << std::endl;

	for (int i = 0; i < nodeStore->size; ++i) {
		if (algo->closed[i] == 1) {
			int node = i;
			fs << std::setprecision(16) << node << "," << nodeStore->x[node] << "," << nodeStore->y[node] << std::endl;
		}
	}
	fs.close();

	// do the shortestPath
	fs.open(shortestPathFile, std::fstream::out);
	fs << "id,linestring" << std::endl;

	int current = from;
	int next = algo->next[current];
	int edgeId = 0;

	while (true) {

		double x1 = nodeStore->x[next];
		double y1 = nodeStore->y[next];

		double x2 = nodeStore->x[current];
		double y2 = nodeStore->y[current];

		current = next;
		next = algo->next[current];

		fs << std::setprecision(16) << (edgeId++) << ";LINESTRING(" << x1 << " " << y1 << "," << x2 << " " << y2 << ")" << std::endl;

		if (current == to) {
			break;
		}
	}

	fs.close();
}

void GISVisualizer::writeAStarBinaryHeap(const char* heapNodeFile, const char* closedNodeFile, const char* shortestPathFile, AStarBidirectionalBinaryHeap* algo) {

	int from = algo->from;
	int to = algo->to;

	NodeStore* nodeStore = algo->nodeStore;

	// do the heapFile
	std::fstream fs;
	fs.open(heapNodeFile, std::fstream::out);
	fs << "id,x,y" << std::endl;

	BinaryHeap<double>* heap = algo->forwardHeap;
	for (int i = 0; i < heap->size; ++i) {
		int node = heap->nodeArray[i];
		fs << std::setprecision(16) << node << "," << nodeStore->x[node] << "," << nodeStore->y[node] << std::endl;
	}
	heap = algo->backwardHeap;
	for (int i = 0; i < heap->size; ++i) {
		int node = heap->nodeArray[i];
		fs << std::setprecision(16) << node << "," << nodeStore->x[node] << "," << nodeStore->y[node] << std::endl;
	}

	fs.close();

	// do the closedFile
	fs.open(closedNodeFile, std::fstream::out);
	fs << "id,x,y" << std::endl;

	for (int i = 0; i < nodeStore->size; ++i) {
		if (algo->closed[i] == 1) {
			int node = i;
			fs << std::setprecision(16) << node << "," << nodeStore->x[node] << "," << nodeStore->y[node] << std::endl;
		}
	}
	fs.close();

	// do the shortestPath
	fs.open(shortestPathFile, std::fstream::out);
	fs << "id,linestring" << std::endl;

	int current = algo->meetingNode;
	int previous = algo->previous[current];
	int edgeId = 0;

	while (true) {

		double x1 = nodeStore->x[previous];
		double y1 = nodeStore->y[previous];
		double x2 = nodeStore->x[current];
		double y2 = nodeStore->y[current];

		previous = current;
		current = algo->previous[current];

		fs << std::setprecision(16) << (edgeId++) << ";LINESTRING(" << x1 << " " << y1 << "," << x2 << " " << y2 << ")" << std::endl;

		if (current == from) {
			break;
		}
	}

	current = algo->meetingNode;
	int next = algo->next[current];

	while (true) {

		double x1 = nodeStore->x[next];
		double y1 = nodeStore->y[next];

		double x2 = nodeStore->x[current];
		double y2 = nodeStore->y[current];

		current = next;
		next = algo->next[current];

		fs << std::setprecision(16) << (edgeId++) << ";LINESTRING(" << x1 << " " << y1 << "," << x2 << " " << y2 << ")" << std::endl;

		if (current == to) {
			break;
		}
	}

	fs.close();

}

void GISVisualizer::writeSimplifiedRoads(const char* fileName, NodeStore* nodeStore, SimplifiedRoadStore* simplifiedRoadStore) {
	std::fstream fs;
	fs.open(fileName, std::fstream::out);

	fs << "id;linestring" << std::endl;

	int id = 0;

	for (int i = 0; i < simplifiedRoadStore->size; ++i) {
		double x1 = nodeStore->x[simplifiedRoadStore->startNode[i]];
		double y1 = nodeStore->y[simplifiedRoadStore->startNode[i]];
		double x2 = nodeStore->x[simplifiedRoadStore->endNode[i]];
		double y2 = nodeStore->y[simplifiedRoadStore->endNode[i]];
		fs << std::setprecision(16) << id++ << ";LINESTRING(" << x1 << " " << y1 << "," << x2 << " " << y2 << ")" << std::endl;
	}

	fs.close();
}
