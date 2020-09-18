#pragma once

#include "common.h"
#include "entity.h"

class Room;

class Creature : public Entity
{
public:
	Creature(World& world, EntityType type, const char* name, const char* description, Room& location);
	~Creature();

	Room* location;
};
