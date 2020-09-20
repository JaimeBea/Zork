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
		int damage,
		bool is_container,
		const Item* key
	);
	~Item();

	void Inspect() const override;

	void ChangeParent(Entity& new_parent);

	Entity* parent;
	ItemType item_type;
	const int damage;
	const bool is_container;
};
