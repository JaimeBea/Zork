#pragma once

#include "common.h"

enum class EntityType
{
	Room,
	Exit,
	Player,
	Item
};

class World;

class Entity
{
public:
	Entity(World& world, EntityType entity_type, const std::string& name, const std::string& description);
	~Entity();

	virtual void Inspect() const;

	World* const world;
	EntityType entity_type;
	std::string name;
	std::string description;
	std::list<Entity*> contains;
};
