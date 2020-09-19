#pragma once

#include "entity.h"

class Item : public Entity
{
public:
	Item(World& world, Entity& parent, std::string name, std::string description);
	~Item();

	void Inspect() const override;

	Entity* parent;
};
