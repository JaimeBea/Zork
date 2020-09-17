#include "common.h"

Direction GetOppositeDirection(const Direction direction)
{
	switch (direction)
	{
	case Direction::North:
		return Direction::South;
	case Direction::East:
		return Direction::West;
	case Direction::South:
		return Direction::North;
	case Direction::West:
		return Direction::East;
	default:
		return Direction::South;
	}
}

void Tokenize(const std::string& input, std::vector<std::string>& output)
{
	output.clear();

	size_t prev = 0;
	size_t next = 0;

	next = input.find_first_of(' ', prev);
	while (next != std::string::npos)
	{
		output.push_back(input.substr(prev, next - prev));

		prev = next + 1;
		next = input.find_first_of(' ', prev);
	}
}
