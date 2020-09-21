#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "npc.h"

Player::Player
(
	World& world,
	Room& location,
	const std::string& name,
	const std::string& description,
	int health,
	float damage_multiplier
)
	: Creature(world, location, EntityType::Player, name, description, health, damage_multiplier)
{
	location.Inspect();
}

void Player::Damage(int damage)
{
	const int previous_health = health;

	Creature::Damage(damage);

	if (health == 0)
	{
		std::cout << "You die and ascend to heaven.\n";
	}
	else if (health < starting_health / 2 && previous_health >= starting_health / 2)
	{
		std::cout << "You are wounded!\n";
	}
	else if (health < starting_health / 4 && previous_health >= starting_health / 4)
	{
		std::cout << "You are in critical condition!\n";
	}
}

bool CheckIsBodyPartEmpty(const Item& body_part)
{
	for (const Entity* const entity : body_part.contains)
	{
		if (entity->entity_type != EntityType::Item)
		{
			return false;
		}

		const Item* const item = dynamic_cast<const Item*>(entity);

		if (item->item_type == ItemType::Pickable)
		{
			return false;
		}
	}

	return true;
}

bool Player::OnExamine(const std::string& name) const
{
	if (name == "")
	{
		location->Inspect();
		return true;
	}
	else
	{
		const Entity* const entity = location->SearchEntity(name);
		if (entity != nullptr)
		{
			entity->Inspect();
			return true;
		}
	}

	return false;
}

bool Player::OnGo(Direction direction)
{
	// Check if there is an exit in the given direction
	const Exit* const exit = location->GetExit(direction);
	if (exit == nullptr)
	{
		std::cout << "You can't go " << GetDirectionName(direction) << ".\n";
		return false;
	}
	if (exit->key != nullptr)
	{
		std::cout << "The door is locked with a key.\n";
		return false;
	}

	// Move the player
	Room* target;
	if (exit->origin == location)
	{
		target = exit->destination;
	}
	else
	{
		target = exit->origin;
	}
	location->contains.remove(this);
	location = target;
	target->contains.push_back(this);

	// Examine the new room
	target->Inspect();
	return true;
}

Item* RecursivelySearchEmptyBodyPart(const Entity& parent)
{
	for (Entity* const entity : parent.contains)
	{
		if (entity->entity_type != EntityType::Item)
		{
			// Not an item
			continue;
		}

		Item* const item = dynamic_cast<Item*>(entity);
		if (item->item_type != ItemType::BodyPart)
		{
			// Not a body part
			continue;
		}

		if (item->is_container && CheckIsBodyPartEmpty(*item))
		{
			// Empty body part
			return item;
		}

		Item* const found_empty_body_part = RecursivelySearchEmptyBodyPart(*item);
		if (found_empty_body_part != nullptr)
		{
			return found_empty_body_part;
		}
	}

	return nullptr;
}

bool Player::OnTake(const std::string& name)
{
	Entity* const entity = location->SearchEntity(name);
	if (entity == nullptr)
	{
		// Unknown name
		std::cout << "The thing you tried to take doesn't exist.\n";
		return false;
	}

	bool action_taken = false;
	if (entity->entity_type != EntityType::Item)
	{
		// Not an item
		std::cout << "You can't pick up '" << entity->name << "'.\n";
		return false;
	}

	Item* const item = dynamic_cast<Item*>(entity);
	if (item->item_type != ItemType::Pickable)
	{
		// Not a valid item
		std::cout << "You can't pick up '" << item->name << "'.\n";
		return false;
	}

	Item* const empty_body_part = RecursivelySearchEmptyBodyPart(*this);
	if (empty_body_part == nullptr)
	{
		// No empty body part found
		std::cout << "You have no empty hands.\n";
		return false;
	}


	// Check if we are attempting to steal
	Entity* const item_owner = item->GetOwner();
	if (item_owner->entity_type == EntityType::NPC)
	{
		if (item_owner->health == 0)
		{
			// We can steal
			item->ChangeParent(*empty_body_part);
			std::cout << "You take '" << item->name << "' from '" << item_owner->name << "'.\n";
			return true;
		}
		else
		{
			// We can't steal
			std::cout << "'" << item_owner->name << "' notices you trying to steal from him and stops you.\n";
			return true;
		}
	}
	else
	{
		// Normal item take
		item->ChangeParent(*empty_body_part);
		std::cout << "You take '" << item->name << "'.\n";
		return true;
	}
}

bool Player::OnDrop(const std::string& name)
{
	Entity* const entity = SearchEntity(name);
	if (entity == nullptr)
	{
		// Unknown name
		std::cout << "The thing you tried to drop doesn't exist.\n";
		return false;
	}

	bool action_taken = false;
	if (entity->entity_type != EntityType::Item)
	{
		// Not a valid object
		std::cout << "You can't drop '" << entity->name << "'.\n";
		return false;
	}

	Item* const item = dynamic_cast<Item*>(entity);
	if (item->item_type != ItemType::Pickable)
	{
		// Not a vaild item
		std::cout << "You can't drop '" << item->name << "'.\n";
		return false;
	}

	// Drop the item
	item->ChangeParent(*location);
	std::cout << "You drop '" << item->name << "'.\n";
	return true;
}

bool Player::OnPut(const std::string & name, const std::string & container_name)
{
	Entity* const entity = SearchEntity(name);
	if (entity == nullptr)
	{
		// Unknown source name
		std::cout << "You aren't holding any item with that name.\n";
		return false;
	}

	Entity* const container_entity = location->SearchEntity(container_name);
	if (container_entity == nullptr)
	{
		// Unknown target name
		std::cout << "The object you tried to place the item in doesn't exist.\n";
		return false;
	}

	// Check if we can drop the item
	Item* selected_item = nullptr;
	if (entity->entity_type == EntityType::Item)
	{
		Item* const item = dynamic_cast<Item*>(entity);
		if (item->item_type == ItemType::Pickable)
		{
			// Valid item
			selected_item = item;
		}
	}

	if (selected_item == nullptr)
	{
		// Not a valid item to drop
		std::cout << "You can't drop '" << entity->name << "'.\n";
		return false;
	}

	bool item_moved = false;
	if (container_entity->entity_type != EntityType::Item)
	{
		// Not an item
		std::cout << "You can't put '" << selected_item->name << "' in '" << container_entity->name << "'.\n";
		return false;
	}

	Item* const container_item = dynamic_cast<Item*>(container_entity);
	if (!container_item->is_container)
	{
		// Not a container
		std::cout << "You can't put '" << selected_item->name << "' in '" << container_item->name << "'.\n";
		return false;
	}

	if (container_item->key != nullptr)
	{
		// Closed with a key
		std::cout << "'" << container_item->name << "' is closed with a key.\n";
		return false;
	}

	if (container_item->item_type == ItemType::BodyPart && !CheckIsBodyPartEmpty(*container_item))
	{
		// Full body part
		std::cout << "You can't put '" << selected_item->name << "' in '" << container_item->name << "'.\n";
		return false;
	}

	if (container_item == selected_item)
	{
		// Recursive put is not allowed
		std::cout << "You can't put '" << selected_item->name << "' in '" << container_item->name << "'.\n";
		return false;
	}

	// Put the item in the container
	selected_item->ChangeParent(*container_item);
	std::cout << "You put '" << selected_item->name << "' in '" << container_item->name << "'.\n";
	return true;
}

bool Player::OnHit(const std::string& target_name, const std::string& source_name)
{
	Entity* const source_entity = SearchEntity(source_name);
	if (source_entity == nullptr)
	{
		std::cout << "The thing you tried to hit with doesn't exist.\n";
		return false;
	}

	Entity* const target_entity = location->SearchEntity(target_name);
	if (target_entity == nullptr)
	{
		std::cout << "The thing you tried to hit doesn't exist.\n";
		return false;
	}

	if (source_entity->entity_type != EntityType::Item)
	{
		std::cout << "You can't use '" << source_entity->name << "' to hit anything.\n";
		return false;
	}

	// Damage the target
	Item* const source_item = dynamic_cast<Item*>(source_entity);

	std::cout << "You hit '" << target_entity->name << "' with '" << source_item->name << "'!\n";
	target_entity->Damage(source_item->damage);

	return true;
}

bool Player::OnOpen(const std::string& name)
{
	Entity* const entity = location->SearchEntity(name);
	if (entity == nullptr)
	{
		// Unknown name
		std::cout << "The thing you tried to open doesn't exist.\n";
		return false;
	}
	if (entity->key == nullptr)
	{
		// No key needed
		std::cout << "You can't open '" << entity->name << "' with a key.\n\n";
		return false;
	}

	Entity* const key = SearchEntity(entity->key->name);
	if (key == nullptr)
	{
		// No key
		std::cout << "You can't open '" << entity->name << "' without '" << entity->key->name << "'.\n";
		return false;
	}

	// Open the entity
	entity->key = nullptr;
	std::cout << "You open '" << entity->name << "' with '" << key->name << "'.\n";
	return true;
}
