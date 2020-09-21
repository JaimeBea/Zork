#pragma once

#include "common.h"
#include "entity.h"

enum class ItemType
{
	Furniture,
	Pickable,
	BodyPart
};

class World;
class Room;

class Item : public Entity
{
public:
	Item
	(
		World& world,
		Entity& parent,
		ItemType item_type,
		const std::string& name,
		const std::string& description,
		int health,
		float damage_multiplier,
		int damage,
		bool is_container,
		Item* key
	);
	~Item();

	void Inspect() const override;
	void Damage(int damage) override;

	Room* GetRoom() const;
	Entity* GetOwner() const;
	void ChangeParent(Entity& new_parent);

	Entity* parent;
	ItemType item_type;
	int damage;
	bool is_container;
};
