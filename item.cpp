#include "item.h"

Item::Item
(
	World& world,
	Entity& parent,
	ItemType item_type,
	const std::string& name,
	const std::string& description,
	int health,
	int damage,
	bool is_container,
	const Item* key
)
	: Entity(world, EntityType::Item, name, description, health, key),
	parent(&parent),
	item_type(item_type),
	damage(damage),
	is_container(is_container)
{
	parent.contains.push_back(this);
}

Item::~Item()
{
	parent->contains.remove(this);
}

void Item::Inspect() const
{
	Entity::Inspect();

	if (health == 0)
	{
		std::cout << "It's broken.\n";
	}

	if (key != nullptr)
	{
		std::cout << "You need a key to open it.\n";
	}
	else if (!contains.empty())
	{
		std::cout << "\n";
		std::cout << "Contains:\n";
		for (const Entity* const entity : contains)
		{
			if (entity->entity_type == EntityType::Exit) continue;

			std::cout << "  " << entity->name << "\n";
		}
	}
	std::cout << "\n";
}

void Item::ChangeParent(Entity& new_parent)
{
	parent->contains.remove(this);
	new_parent.contains.push_back(this);
	parent = &new_parent;
}
