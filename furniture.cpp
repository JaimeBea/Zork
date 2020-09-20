#include "furniture.h"

Furniture::Furniture(World& world, Entity& parent, const std::string& name, const std::string& description, int health, bool is_container, const Item* key)
	: Item(world, parent, EntityType::Furniture, name, description, health, 0, is_container, key) {}
