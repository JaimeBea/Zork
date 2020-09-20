#include "pickable.h"

Pickable::Pickable(World& world, Entity& parent, const std::string& name, const std::string& description, int health, int damage, bool is_container, const Item* key)
	: Item(world, parent, EntityType::Pickable, name, description, health, damage, is_container, key) {}
