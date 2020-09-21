#include "item.h"
#include "room.h"
#include "creature.h"

Item::Item
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
)
	: Entity(world, EntityType::Item, name, description, health, key),
	parent(&parent),
	item_type(item_type),
	damage(damage),
	is_container(is_container)
{
	parent.contains.push_back(this);
}

Item::~Item()
{
	parent->contains.remove(this);
}

void Item::Inspect() const
{
	Entity::Inspect();

	if (health == 0)
	{
		std::cout << "It's broken.\n";
	}

	if (key != nullptr)
	{
		std::cout << "You need a key to open it.\n";
	}
	else if (!contains.empty())
	{
		std::cout << "Contains:\n";
		for (const Entity* const entity : contains)
		{
			if (entity->entity_type == EntityType::Exit) continue;

			std::cout << "  " << entity->name << "\n";
		}
	}
}

void Item::Damage(int damage)
{
	const int previous_health = health;
	const ItemType previous_item_type = item_type;

	Entity::Damage(damage);

	if (health == 0)
	{
		if (previous_health != 0)
		{
			if (item_type == ItemType::BodyPart)
			{
				std::cout << "The '" << name << "' has been severed.\n";
				item_type = ItemType::Pickable;
			}
			else if (item_type == ItemType::Pickable)
			{
				std::cout << "The '" << name << "' has been broken.\n";
			}

			if (parent->entity_type != EntityType::Room)
			{
				std::cout << "The '" << name << " flies off in an arc.\n";
				Room* const location = GetRoom();
				ChangeParent(*location);
			}
		}
		else
		{
			std::cout << "The '" << name << "' is already broken.\n";
		}
	}

	if (previous_item_type == ItemType::BodyPart)
	{
		// Propagate 50% of the damage to the parent
		parent->Damage(damage / 2);
	}
}

Room* Item::GetRoom() const
{
	if (parent->entity_type == EntityType::Room)
	{
		Room* const parent_room = dynamic_cast<Room*>(parent);
		return parent_room;
	}
	else if (parent->entity_type == EntityType::NPC || parent->entity_type == EntityType::Player)
	{
		Creature* const parent_creature = dynamic_cast<Creature*>(parent);
		return parent_creature->location;
	}
	else if (parent->entity_type == EntityType::Item)
	{
		Item* const parent_item = dynamic_cast<Item*>(parent);
		return parent_item->GetRoom();
	}

	// The item doesn't pertain to a room. This should never happen.
	return nullptr;
}

Entity* Item::GetOwner() const
{
	// If the parent is an item check the item's owner
	if (parent->entity_type == EntityType::Item)
	{
		Item* const parent_item = dynamic_cast<Item*>(parent);
		return parent_item->GetOwner();
	}

	return parent;
}

void Item::ChangeParent(Entity& new_parent)
{
	parent->contains.remove(this);
	new_parent.contains.push_back(this);
	parent = &new_parent;
}
