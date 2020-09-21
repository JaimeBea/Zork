#pragma once

#include "common.h"

enum class EntityType
{
	Room,
	Exit,
	Player,
	NPC,
	Item
};

class World;
class Item;

class Entity
{
public:
	Entity(World& world, EntityType entity_type, const std::string& name, const std::string& description, int health, const Item* key);

	virtual void Inspect() const;
	virtual void Damage(int damage);

	World* const world;
	const EntityType entity_type;
	const std::string name;
	const std::string description;
	std::list<Entity*> contains;
	const int starting_health;
	int health;
	const Item* key;
};
