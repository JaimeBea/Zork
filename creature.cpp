#include "creature.h"
#include "room.h"

Creature::Creature(World& world, EntityType type, std::string name, std::string description, Room& location) : Entity(world, type, name, description), location(&location)
{
	location.contains.push_back(this);
}

Creature::~Creature()
{
	location->contains.remove(this);
}
