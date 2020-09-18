#pragma once

#include "common.h"
#include "entity.h"

class Exit;

class Room : public Entity
{
public:
	Room(World& world, const char* name, const char* description);

	Exit* GetExit(Direction direction) const;
	Room* GetExitRoom(Direction direction) const;
};
