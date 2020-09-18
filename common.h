#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

typedef long EntityID;

enum class Direction
{
	Unknown,
	North,
	East,
	South,
	West
};

std::string GetDirectionName(Direction direction);
Direction GetDirectionFromName(const std::string& name);
Direction GetOppositeDirection(Direction direction);

void Tokenize(const std::string& input, std::vector<std::string>& output);

bool CaseInsensitiveCompare(std::string string1, std::string string2);
