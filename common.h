#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>

enum class Direction
{
	North,
	East,
	South,
	West
};

Direction GetOppositeDirection(const Direction direction);
void Tokenize(const std::string& input, std::vector<std::string>& output);
