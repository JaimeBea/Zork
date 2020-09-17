#pragma once

#include "common.h"

enum class EntityType
{
	Room,
	Exit
};

class Entity
{
public:
	Entity(const EntityType type, const char* name, const char* description);

	EntityType type;
	std::string name;
	std::string description;
	std::list<Entity*> contains;
};

