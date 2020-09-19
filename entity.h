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
	Entity(World& world, EntityType type, std::string name, std::string description);
	~Entity();

	virtual void Inspect() const;

	World& world;
	EntityType type;
	std::string name;
	std::string description;
	std::list<Entity*> contains;
};

