
#include "RoadParser.h"
#include <fstream>
#include "Search.h"
#include "Coordinate.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 16384
#endif

#ifdef _DEBUG
#include <iostream>
#endif

void RoadParser::parseFile(char* fileName, uint64_t* coordinates, int coordinatesCount, std::list<Link>& links)
{
	unsigned char buffer[BUFFER_SIZE];

	FILE* source = fopen(fileName, "rb");

	unsigned int state = 0;
	unsigned int variableA = 0;
	unsigned int variableB = 0;

	uint32_t fileSize = 0;
	uint32_t fileShapeType = 0;

	uint64_t xMinInteger = 0;
	uint64_t yMinInteger = 0;
	uint64_t xMaxInteger = 0;
	uint64_t yMaxInteger = 0;

	unsigned int recordNumber = 0;
	unsigned int contentLength = 0;

	uint32_t shapeType = 0;
	uint32_t numParts = 0;
	uint32_t numPoints = 0;

	uint32_t part = 0;
	uint64_t coordinate = 0;

	double x;
	double y;

	int allCoordinates = 0;
	int allVertexCoordinates = 0;

	int v1 = -1;

	while (!feof(source))
	{
		int readedBytes = fread(buffer, 1, BUFFER_SIZE, source);

		for (int i = 0; i < readedBytes; ++i)
		{
			if (state == 0 && variableA < 23)
			{
				++variableA;
			}
			else if (state == 0)
			{
				state = 1;
				variableA = 24;
			}
			else if (state == 1)
			{
				fileSize |= static_cast<uint32_t>(buffer[i]) << variableA;
				if (variableA == 0)
				{
					state = 2;
					variableA = 0;
				}
				else
				{
					variableA -= 8;
				}
			}
			else if (state == 2 && variableA < 3)
			{
				++variableA;
			}
			else if (state == 2)
			{
				state = 3;
				variableA = 0;
			}
			else if (state == 3)
			{
				fileShapeType |= static_cast<uint32_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 32)
				{
					state = 4;
					variableA = 0;
				}
			}
			else if (state == 4)
			{
				xMinInteger |= static_cast<uint64_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 64)
				{
					state = 5;
					variableA = 0;
				}
			}
			else if (state == 5)
			{
				yMinInteger |= static_cast<uint64_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 64)
				{
					state = 6;
					variableA = 0;
				}
			}
			else if (state == 6)
			{
				xMaxInteger |= static_cast<uint64_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 64)
				{
					state = 7;
					variableA = 0;
				}
			}
			else if (state == 7)
			{
				yMaxInteger |= static_cast<uint64_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 64)
				{
					state = 8;
					variableA = 0;
				}
			}
			else if (state == 8 && variableA < 31)
			{
				++variableA;
			}
			else if (state == 8)
			{
				state = 9;
				variableA = 24;
			}
			else if (state == 9)
			{
				recordNumber |= static_cast<uint32_t>(buffer[i]) << variableA;
				if (variableA == 0)
				{
					state = 10;
					variableA = 24;
				}
				else
				{
					variableA -= 8;
				}
			}
			else if (state == 10)
			{
				contentLength |= static_cast<uint32_t>(buffer[i]) << variableA;
				if (variableA == 0)
				{
					state = 11;
					variableA = 0;
					shapeType = 0;
				}
				else
				{
					variableA -= 8;
				}
			}
			else if (state == 11)
			{
				shapeType |= static_cast<uint32_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 32)
				{
					state = 12;
					variableA = 0;
				}
			}
			else if (state == 12 && variableA < 31)
			{
				++variableA;
			}
			else if (state == 12)
			{
#ifdef _DEBUG
				if (shapeType != 3)
				{
					std::cout << "hhhhmmm" << std::endl;
				}
#endif	
				state = 13;
				variableA = 0;
				numParts = 0;
				numPoints = 0;
			}
			else if (state == 13)
			{
				numParts |= static_cast<uint32_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 32)
				{
					state = 14;
					variableA = 0;
				}
			}
			else if (state == 14)
			{
				numPoints |= static_cast<uint32_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 32)
				{
					state = 15;
					variableA = 0;
					variableB = 0;
				}
			}
			else if (state == 15)
			{
				part |= static_cast<uint32_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 32)
				{
					++variableB;
					if (variableB == numParts)
					{
						variableA = 0;
						variableB = 0;
						part = 0;
						state = 17;
					}
					else
					{
						part = 0;
						variableA = 0;
					}
				}
			}
			else if (state == 17)
			{
				coordinate |= static_cast<uint64_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 64)
				{
					x = *(double*)(&coordinate);
					coordinate = 0;

					state = 18;
					variableA = 0;
				}
			}
			else if (state == 18)
			{
				coordinate |= static_cast<uint64_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 64)
				{
					y = *(double*)(&coordinate);
					coordinate = 0;

					uint64_t c = Coordinate::getHash(x, y);
#ifdef _DEBUG
					++allCoordinates;
					if (Search::binary_search(coordinates, 0, coordinatesCount, c) != -1)
					{
						++allVertexCoordinates;
					}
#endif
					int v = Search::binary_search(coordinates, 0, coordinatesCount, c);
					if (v != -1)
					{
						if (v1 == -1)
						{
							v1 = v;
						}
						else
						{
							Link link(v1, v);
							links.push_back(link);
							v1 = v;
						}
					}
					state = 17;
					variableA = 0;

					++variableB;
					if (variableB == numPoints)		
					{
						v1 = -1;

						variableA = 0;
						variableB = 0;

						coordinate = 0;

						state = 9;
						variableA = 24;
						recordNumber = 0;
						contentLength = 0;
					}
					else
					{
						coordinate = 0;
						variableA = 0;
					}
				}
			}
		}

	}

#ifdef _DEBUG
	std::cout << "allCoordinatesInTheRoad: " << allCoordinates << std::endl;
	std::cout << "allVertexCoordinates: " << allVertexCoordinates << std::endl;
	std::cout << "links: " << links.size() << std::endl;
#endif
}

Link::Link(int v1, int v2)
{
	this->v1 = v1;
	this->v2 = v2;
}
