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
	Entity
	(
		World& world,
		EntityType entity_type,
		const std::string& name,
		const std::string& description,
		int health,
		float damage_multiplier,
		Item* key
	);

	virtual void Update();
	virtual void Inspect() const;
	virtual void Damage(int damage);
	Entity* SearchEntity(const std::string& name) const;

	World* const world;
	EntityType entity_type;
	std::string name;
	std::string description;
	std::list<Entity*> contains;
	int starting_health;
	int health;
	float damage_multiplier;
	Item* key;
};
