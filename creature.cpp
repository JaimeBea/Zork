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

void Creature::Inspect() const
{
	std::cout << name << ":\n";
	std::cout << description << "\n\n";

	if (!contains.empty())
	{
		std::cout << "Inventory:\n";
		for (const Entity* const entity : contains)
		{
			if (entity->entity_type == EntityType::Exit) continue;

			std::cout << "  " << entity->name << "\n";
		}
		std::cout << "\n";
	}
}
