#pragma once

#include "common.h"
#include "item.h"

class World;
class Entity;

class Furniture : public Item
{
public:
	Furniture(World& world, Entity& parent, const std::string& name, const std::string& description, int health, bool is_container = false);
};

