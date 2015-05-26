#include "JunctionParser.h"
#include <fstream>
#include "Coordinate.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 16384
#endif

#ifdef _DEBUG
#include <iostream>
#endif

int compare(const void * a, const void * b)
{
	if (*(uint64_t*)a <  *(uint64_t*)b) return -1;
	if (*(uint64_t*)a == *(uint64_t*)b) return 0;
	return 1;
}

bool JunctionParser::parseFile(char* fileName, uint64_t*& coordinates, int& coordinatesCount)
{
	int coordinatesIndex = 0;

#ifdef _DEBUG
	std::cout.precision(3);
#endif

	unsigned char buffer[BUFFER_SIZE];

	FILE* source = fopen(fileName, "rb");

	unsigned int state = 0;
	unsigned int variableA = 0;

	uint32_t fileSize = 0;
	uint32_t fileShapeType = 0;

	uint64_t xMinInteger = 0;
	uint64_t yMinInteger = 0;
	uint64_t xMaxInteger = 0;
	uint64_t yMaxInteger = 0;

	unsigned int recordNumber = 0;
	unsigned int contentLength = 0;

	uint32_t shapeType = 0;
	uint64_t x = 0;
	uint64_t y = 0;

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
					coordinatesCount = (fileSize * 2 - 100) / 28;
					coordinates = new uint64_t[coordinatesCount];
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
					x = 0;
					y = 0;
				}
			}
			else if (state == 12)
			{
				x |= static_cast<uint64_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 64)
				{
					state = 13;
					variableA = 0;
				}
			}
			else if (state == 13)
			{
				y |= static_cast<uint64_t>(buffer[i]) << variableA;
				variableA += 8;
				if (variableA == 64)
				{
					double xDouble = *(double*)(&x);
					double yDouble = *(double*)(&y);

					uint64_t coordinate = Coordinate::getHash(xDouble, yDouble);

					coordinates[coordinatesIndex] = coordinate;
					++coordinatesIndex;

					state = 9;
					variableA = 24;
					recordNumber = 0;
					contentLength = 0;
					shapeType = 0;
				}
			}
		}

	}
	qsort(coordinates, coordinatesCount, sizeof(uint64_t), compare);

#ifdef _DEBUG
	std::cout << "fileSize: " << fileSize << std::endl;
	std::cout << "fileShapeType: " << fileShapeType << std::endl;
	double xMin = *(double*)(&xMinInteger);
	double xMax = *(double*)(&xMaxInteger);
	double yMin = *(double*)(&yMinInteger);
	double yMax = *(double*)(&yMaxInteger);
	std::cout << "xMin: " << std::fixed << xMin << std::endl;
	std::cout << "xMax: " << std::fixed << xMax << std::endl;
	std::cout << "yMin: " << std::fixed << yMin << std::endl;
	std::cout << "yMax: " << std::fixed << yMax << std::endl;
	std::cout << "recordNumber: " << recordNumber << std::endl;
	std::cout << "contentLength: " << contentLength << std::endl;
#endif

	fclose(source);

	return true;
}