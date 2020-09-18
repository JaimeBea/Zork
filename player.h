#pragma once

#include "common.h"
#include "creature.h"

class Room;

class Player : public Creature
{
public:
	Player(World& world, const char* name, const char* description, Room& location);

	bool Go(Direction direction);
};
