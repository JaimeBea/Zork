#include "body_part.h"

BodyPart::BodyPart(World& world, Entity& parent, const std::string& name, const std::string& description, int health, int damage, bool is_attached, bool is_container)
	: Item(world, parent, EntityType::BodyPart, name, description, health, damage, is_container), is_attached(is_attached) {}
