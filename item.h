#pragma once

#include "common.h"
#include "entity.h"

class World;
class Room;

class Item : public Entity
{
public:
	Item(World& world, Entity& parent, EntityType type, const std::string& name, const std::string& description, int health, int damage, bool is_container = false);
	~Item();

	void Inspect() const override;

	void ChangeParent(Entity& new_parent);

	Entity* parent;
	int damage;
	bool is_container;
};
