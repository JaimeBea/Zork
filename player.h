#pragma once

#include "common.h"
#include "creature.h"

class Room;

class Player : public Creature
{
public:
	Player(World& world, const std::string& name, const std::string& description, Room& location);

	bool Examine(const std::string& name);
	bool Go(Direction direction);
};
