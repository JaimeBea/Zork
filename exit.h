#pragma once

#include "common.h"
#include "entity.h"

class Room;

class Exit : public Entity
{
public:
	Exit(World& world, const char* name, const char* description, Room& origin, Room& destination, Direction direction);
	~Exit();

	Room& origin;
	Room& destination;
	Direction direction;
};
