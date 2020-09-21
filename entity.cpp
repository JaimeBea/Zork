#include "entity.h"
#include "world.h"

Entity::Entity(World& world, EntityType entity_type, const std::string& name, const std::string& description, int health, const Item* key)
	: world(&world), entity_type(entity_type), name(name), description(description), starting_health(health), health(health), key(key)
{
	world.entities.push_back(this);
}

void Entity::Inspect() const
{
	std::cout << name << ":\n";
	std::cout << "  " << description << "\n";
}

void Entity::Damage(int damage)
{
	health = std::max(0, health - damage);
}
