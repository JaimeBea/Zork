#include "creature.h"
#include "room.h"
#include "item.h"

Creature::Creature
(
	World& world,
	Room& location,
	EntityType entity_type,
	const std::string& name,
	const std::string& description,
	int health,
	float damage_multiplier
)
	: Entity(world, entity_type, name, description, health, damage_multiplier, nullptr),
	location(&location)
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
		if (entity->entity_type != EntityType::Item)
		{
			// Not an item (this should never happen)
			continue;
		}

		const Item* const item = dynamic_cast<const Item*>(entity);
		if (item->item_type == ItemType::BodyPart)
		{
			ListInventoryRecursive(item);
		}
		else
		{
			std::cout << "  " << item->name << " (" << parent->name << ")\n";
		}
	}
}

void Creature::Inspect() const
{
	Entity::Inspect();

	if (health == 0)
	{
		std::cout << "Health Status:\n";
		std::cout << "  Deceased.\n";
	}
	else if (health < starting_health / 2)
	{
		std::cout << "Health Status:\n";
		std::cout << "  Wounded.\n";
	}
	else if (health < starting_health / 4)
	{
		std::cout << "Health Status:\n";
		std::cout << "  Critical.\n";
	}

	if (!contains.empty())
	{
		std::cout << "Holding:\n";
		ListInventoryRecursive(this);

		std::cout << "Body:\n";
		for (const Entity* const entity : contains)
		{
			if (entity->entity_type != EntityType::Item)
			{
				// Not an item (this should never happen)
				continue;
			}

			const Item* const item = dynamic_cast<const Item*>(entity);
			if (item->item_type == ItemType::BodyPart)
			{
				std::cout << "  " << item->name << "\n";
			}
		}
	}
}
