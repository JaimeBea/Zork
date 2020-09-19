#include "item.h"

Item::Item(World& world, Entity& parent, std::string name, std::string description) : Entity(world, EntityType::Item, name, description), parent(&parent)
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
		for (Entity* entity : contains)
		{
			if (entity->type == EntityType::Exit) continue;

			std::cout << "  " << entity->name << "\n";
		}
		std::cout << "\n";
	}
}
