#pragma once

#include "common.h"
#include "item.h"

class World;
class Entity;

class BodyPart : public Item
{
public:
	BodyPart(World& world, Entity& parent, const std::string& name, const std::string& description, int health, int damage, bool is_attached, bool is_container = false);

	bool is_attached;
};
