#include "entity.h"
#include "world.h"

Entity::Entity
(
	World& world,
	EntityType entity_type,
	const std::string& name,
	const std::string& description,
	int health,
	float damage_multiplier,
	Item* key
)
	: world(&world),
	entity_type(entity_type),
	name(name),
	description(description),
	starting_health(health),
	health(health),
	damage_multiplier(damage_multiplier),
	key(key)
{
	world.entities.push_back(this);
}

void Entity::Update() {}

void Entity::Inspect() const
{
	std::cout << name << ":\n";
	std::cout << "  " << description << "\n";
}

void Entity::Damage(int damage)
{
	const int final_damage = damage * damage_multiplier;
	health = std::max(0, health - final_damage);
}

Entity* Entity::SearchEntity(const std::string & name) const
{
	for (Entity* const entity : contains)
	{
		if (CaseInsensitiveCompare(entity->name, name))
		{
			return entity;
		}

		if (entity->key != nullptr)
		{
			// The entity is closed with a key, so we can't look inside
			continue;
		}

		Entity* const child_entity = entity->SearchEntity(name);
		if (child_entity != nullptr)
		{
			return child_entity;
		}
	}

	return nullptr;
}
