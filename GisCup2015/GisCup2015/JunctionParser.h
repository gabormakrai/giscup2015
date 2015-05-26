#pragma once

#include <cstdint>

class JunctionParser
{
private:
public:
	bool parseFile(char* fileName, uint64_t*& coordinates, int& coordinatesCount);
};