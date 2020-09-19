#include "creature.h"
#include "room.h"
#include "item.h"

Creature::Creature(World& world, EntityType entity_type, const std::string& name, const std::string& description, Room& location) : Entity(world, entity_type, name, description), location(&location)
{
	location.contains.push_back(this);
}

Creature::~Creature()
{
	location->contains.remove(this);
}

void ListInventoryRecursive(const Entity* parent)
{
	for (const Entity* const entity : parent->contains)
	{
		if (entity->entity_type != EntityType::Item) continue;

		const Item* const item = dynamic_cast<const Item*>(entity);

		if (!item->is_attached)
		{
			std::cout << "  " << item->name << " (" << parent->name << ")\n";
		}
		else
		{
			ListInventoryRecursive(item);
		}
	}
}

void Creature::Inspect() const
{
	std::cout << name << ":\n";
	std::cout << description << "\n\n";

	if (!contains.empty())
	{
		std::cout << "Holding:\n";
		ListInventoryRecursive(this);
		std::cout << "\n";

		std::cout << "Body:\n";
		for (const Entity* const entity : contains)
		{
			if (entity->entity_type != EntityType::Item) continue;

			const Item* const item = dynamic_cast<const Item*>(entity);

			if (item->is_attached)
			{
				std::cout << "  " << item->name << "\n";
			}
		}
		std::cout << "\n";
	}
}
