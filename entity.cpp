#include "entity.h"
#include "world.h"

Entity::Entity(World& world, EntityType type, const char* name, const char* description) : world(world), type(type), name(name), description(description)
{
	world.entities.push_back(this);
}

Entity::~Entity()
{
	std::vector<Entity*>& entities = world.entities;
	for (int i = 0; i < entities.size(); ++i)
	{
		if (entities[i] == this)
		{
			entities.erase(entities.begin() + i);
			break;
		}
	}
}
