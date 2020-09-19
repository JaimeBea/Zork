#include "creature.h"
#include "room.h"

Creature::Creature(World& world, EntityType entity_type, const std::string& name, const std::string& description, Room& location) : Entity(world, entity_type, name, description), location(&location)
{
	location.contains.push_back(this);
}

Creature::~Creature()
{
	location->contains.remove(this);
}
