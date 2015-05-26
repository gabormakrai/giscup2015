#include "LinkProcessor.h"

#include <iostream>

void LinkProcessor::process(std::list<Link> links, int coordinatesCount)
{
//	uint32_t* vertexInDegree = new uint32_t[coordinatesCount];
	uint32_t* vertexOutDegree = new uint32_t[coordinatesCount];
	for (int i = 0; i < coordinatesCount; ++i) {
//		vertexInDegree[i] = 0;
		vertexOutDegree[i] = 0;
	}

	for (std::list<Link>::iterator it = links.begin(); it != links.end(); it++)
	{
		++vertexOutDegree[(*it).v1];
//		++vertexInDegree[(*it).v2];
	}

//	uint32_t* inNeighbours = new uint32_t[links.size()];
	uint32_t* outNeighbours = new uint32_t[links.size()];
//	uint32_t* vertexInOffset = new uint32_t[coordinatesCount];
	uint32_t* vertexOutOffset = new uint32_t[coordinatesCount];

//	int inIndex = 0;
	int outIndex = 0;

//	vertexInOffset[0] = 0;
	vertexOutOffset[0] = 0;

	for (int i = 1; i < coordinatesCount; ++i)
	{
//		inIndex += vertexInDegree[i];
//		vertexInOffset[i] = inIndex;
		outIndex += vertexOutDegree[i - 1];
		vertexOutOffset[i] = outIndex;
	}

	for (int i = 0; i < coordinatesCount; ++i)
	{
//		vertexInDegree[i] = 0;
		vertexOutDegree[i] = 0;
	}

	for (std::list<Link>::iterator it = links.begin(); it != links.end(); it++)
	{
		int v1 = (*it).v1;
		int v2 = (*it).v2;

//		inNeighbours[vertexInOffset[v2] + vertexInDegree[v2]] = v1;
		outNeighbours[vertexOutOffset[v1] + vertexOutDegree[v1]] = v2;

		++vertexOutDegree[v1];
//		++vertexInDegree[v2];
	}

	int v = 123;
}
