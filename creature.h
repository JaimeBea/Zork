#pragma once

#include "common.h"
#include "entity.h"

class Room;

class Creature : public Entity
{
public:
	Creature(World& world, EntityType entity_type, const std::string& name, const std::string& description, Room& location);
	~Creature();

	void Inspect() const override;

	Room* location;
};
