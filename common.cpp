#include "common.h"

const char* GetDirectionName(Direction direction)
{
	switch (direction)
	{
	case Direction::North:
		return "north";
	case Direction::East:
		return "east";
	case Direction::South:
		return "south";
	case Direction::West:
		return "west";
	default:
		return "unknown";
	}
}

Direction GetDirectionFromName(const std::string& name)
{
	if (name == "north")
	{
		return Direction::North;
	}
	else if (name == "east")
	{
		return Direction::East;
	}
	else if (name == "south")
	{
		return Direction::South;
	}
	else if (name == "west")
	{
		return Direction::West;
	}

	return Direction::Unknown;
}

Direction GetOppositeDirection(Direction direction)
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
		return Direction::Unknown;
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
	output.push_back(input.substr(prev, next - prev));
}
