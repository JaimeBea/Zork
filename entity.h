#pragma once

#include "common.h"

enum class EntityType
{
	Room,
	Exit,
	Player
};

class World;

class Entity
{
public:
	Entity(World& world, EntityType type, const char* name, const char* description);
	~Entity();

	void Inspect() const;

	World& world;
	EntityType type;
	std::string name;
	std::string description;
	std::list<Entity*> contains;
};

