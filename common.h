#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

typedef long EntityID;

enum class Direction
{
	Unknown,
	North,
	East,
	South,
	West
};

const char* GetDirectionName(Direction direction);
Direction GetDirectionFromName(const std::string& name);
Direction GetOppositeDirection(Direction direction);

void Tokenize(const std::string& input, std::vector<std::string>& output);
