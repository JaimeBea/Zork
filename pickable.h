#pragma once

#include "common.h"
#include "item.h"

class World;
class Entity;

class Pickable : public Item
{
public:
	Pickable(World& world, Entity& parent, const std::string& name, const std::string& description, int health, int damage, bool is_container = false);
};


