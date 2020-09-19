#pragma once

#include "entity.h"

class Item : public Entity
{
public:
	Item(World& world, Entity& parent, const std::string& name, const std::string& description, bool is_container, bool is_big, bool is_attached);
	~Item();

	void Inspect() const override;

	void ChangeParent(Entity& new_parent);

	Entity* parent;
	bool is_container;
	bool is_big;
	bool is_attached;
};
