#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>

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
std::string JoinTokens(const std::vector<std::string>& tokens, int start, int end);

bool CaseInsensitiveCompare(const std::string& string1, const std::string& string2);
