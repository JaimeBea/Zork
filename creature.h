#pragma once

#include "common.h"
#include "entity.h"

class World;
class Room;

class Creature : public Entity
{
public:
	Creature
	(
		World& world,
		Room& location,
		EntityType entity_type,
		const std::string& name,
		const std::string& description,
		int health,
		float damage_multiplier
	);
	~Creature();

	void Inspect() const override;

	Room* location;
};
