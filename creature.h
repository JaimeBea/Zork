#pragma once

#include "common.h"
#include "entity.h"

class Room;

class Creature : public Entity
{
public:
	Creature(World& world, EntityType type, std::string name, std::string description, Room& location);
	~Creature();

	Room* location;
};
