#include "item.h"

Item::Item(World& world, Entity& parent, ItemType item_type, const std::string& name, const std::string& description) : Entity(world, EntityType::Item, name, description), parent(&parent), item_type(item_type)
{
	parent.contains.push_back(this);
}

Item::~Item()
{
	parent->contains.remove(this);
}

void Item::Inspect() const
{
	std::cout << name << ":\n";
	std::cout << description << "\n\n";

	if (!contains.empty())
	{
		std::cout << "Contains:\n";
		for (const Entity* const entity : contains)
		{
			if (entity->entity_type == EntityType::Exit) continue;

			std::cout << "  " << entity->name << "\n";
		}
		std::cout << "\n";
	}
}

void Item::ChangeParent(Entity& new_parent)
{
	parent->contains.remove(this);
	new_parent.contains.push_back(this);
	parent = &new_parent;
}
