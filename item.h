#pragma once

#include "entity.h"

enum class ItemType
{
	Object,
	Furniture
};

class Item : public Entity
{
public:
	Item(World& world, Entity& parent, ItemType item_type, const std::string& name, const std::string& description);
	~Item();

	void Inspect() const override;

	Entity* parent;
	ItemType item_type;
};
