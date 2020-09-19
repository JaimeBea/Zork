#include "item.h"

Item::Item(World& world, Entity& parent, const std::string& name, const std::string& description, bool is_container, bool is_big, bool is_attached) : Entity(world, EntityType::Item, name, description), parent(&parent), is_container(is_container), is_big(is_big), is_attached(is_attached)
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
