#pragma once

#include "common.h"
#include "creature.h"

class Room;

class Player : public Creature
{
public:
	Player(World& world, std::string name, std::string description, Room& location);

	bool Examine(const std::vector<std::string>& tokens);
	bool Go(Direction direction);
};
