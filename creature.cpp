#include "creature.h"
#include "room.h"
#include "body_part.h"

Creature::Creature(World& world, Room& location, EntityType entity_type, const std::string& name, const std::string& description, int health)
	: Entity(world, entity_type, name, description, health, nullptr), location(&location)
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
		if (entity->entity_type == EntityType::Pickable)
		{
			std::cout << "  " << entity->name << " (" << parent->name << ")\n";
		}
		else if (entity->entity_type == EntityType::BodyPart)
		{
			const BodyPart* const body_part = dynamic_cast<const BodyPart*>(entity);

			if (!body_part->is_attached)
			{
				std::cout << "  " << body_part->name << " (" << parent->name << ")\n";
			}
			else
			{
				ListInventoryRecursive(body_part);
			}
		}
	}
}

void Creature::Inspect() const
{
	Entity::Inspect();

	if (health == 0)
	{
		std::cout << "Deceased.\n\n";
	}

	if (!contains.empty())
	{
		std::cout << "Holding:\n";
		ListInventoryRecursive(this);
		std::cout << "\n";

		std::cout << "Body:\n";
		for (const Entity* const entity : contains)
		{
			if (entity->entity_type == EntityType::BodyPart)
			{
				const BodyPart* const body_part = dynamic_cast<const BodyPart*>(entity);

				if (body_part->is_attached)
				{
					std::cout << "  " << body_part->name << "\n";
				}
			}
		}
		std::cout << "\n";
	}
}
