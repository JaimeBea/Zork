#include "player.h"
#include "room.h"
#include "exit.h"
#include "pickable.h"
#include "body_part.h"

Player::Player
(
	World& world,
	Room& location,
	const std::string& name,
	const std::string& description,
	int health
) : Creature(world, location, EntityType::Player, name, description, health)
{
	location.Inspect();
}

bool CheckIsBodyPartEmpty(const BodyPart& body_part)
{
	for (const Entity* const entity : body_part.contains)
	{
		if (entity->entity_type == EntityType::Pickable)
		{
			return false;
		}
		else if (entity->entity_type == EntityType::BodyPart)
		{
			const BodyPart* const body_part = dynamic_cast<const BodyPart*>(entity);

			if (!body_part->is_attached)
			{
				return false;
			}
		}
	}

	return true;
}

Entity* RecursivelySearchEntity(const std::list<Entity*>& entities, const std::string& name)
{
	for (Entity* const entity : entities)
	{
		if (CaseInsensitiveCompare(entity->name, name))
		{
			return entity;
		}

		Entity* const child_entity = RecursivelySearchEntity(entity->contains, name);
		if (child_entity != nullptr)
		{
			return child_entity;
		}
	}

	return nullptr;
}

BodyPart* RecursivelySearchEmptyBodyPart(const Entity& parent)
{
	for (Entity* const entity : parent.contains)
	{
		if (entity->entity_type == EntityType::BodyPart)
		{
			BodyPart* const body_part = dynamic_cast<BodyPart*>(entity);

			if (body_part->is_attached)
			{
				if (body_part->is_container)
				{
					if (CheckIsBodyPartEmpty(*body_part))
					{
						return body_part;
					}
				}
				else
				{
					BodyPart* const found_empty_body_part = RecursivelySearchEmptyBodyPart(*body_part);
					if (found_empty_body_part != nullptr)
					{
						return found_empty_body_part;
					}
				}
			}
		}
	}

	return nullptr;
}

bool Player::Examine(const std::string& name) const
{
	if (name == "")
	{
		location->Inspect();
		return true;
	}
	else
	{
		const Entity* const entity = RecursivelySearchEntity(location->contains, name);
		if (entity != nullptr)
		{
			entity->Inspect();
			return true;
		}
	}

	return false;
}

bool Player::Go(Direction direction)
{
	// Check if there is an exit in the given direction
	const Exit* const exit = location->GetExit(direction);
	if (exit == nullptr)
	{
		std::cout << "You can't go " << GetDirectionName(direction) << "\n\n";
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

bool Player::Take(const std::string& name)
{
	Entity* const entity = RecursivelySearchEntity(location->contains, name);
	if (entity == nullptr)
	{
		// Unknown name
		std::cout << "The thing you tried to take doesn't exist.\n\n";
		return false;
	}

	// Check if we can take the item
	bool item_taken = false;
	if (entity->entity_type == EntityType::BodyPart)
	{
		BodyPart* const body_part = dynamic_cast<BodyPart*>(entity);
		if (!body_part->is_attached)
		{
			BodyPart* const empty_body_part = RecursivelySearchEmptyBodyPart(*this);
			if (empty_body_part != nullptr)
			{
				// Empty body part found
				body_part->ChangeParent(*empty_body_part);

				std::cout << "You take '" << body_part->name << "'.\n\n";
				item_taken = true;
			}
			else
			{
				// No empty body part found
				std::cout << "You have no empty hands.\n\n";
			}
		}
		else
		{
			// The item is an attached body part
			std::cout << "You can't pick up '" << body_part->name << "'.\n\n";
		}
	}
	else if (entity->entity_type == EntityType::Pickable)
	{
		Pickable* const pickable = dynamic_cast<Pickable*>(entity);
		BodyPart* const empty_body_part = RecursivelySearchEmptyBodyPart(*this);
		if (empty_body_part != nullptr)
		{
			// Empty body part found
			pickable->ChangeParent(*empty_body_part);

			std::cout << "You take '" << pickable->name << "'.\n\n";
			item_taken = true;
		}
		else
		{
			// No empty body part found
			std::cout << "You have no empty hands.\n\n";
		}
	}
	else
	{
		// Not a valid item
		std::cout << "You can't pick up '" << entity->name << "'.\n\n";
	}

	return item_taken;
}

bool Player::Drop(const std::string& name)
{
	Entity* const entity = RecursivelySearchEntity(contains, name);
	if (entity == nullptr)
	{
		// Unknown name
		std::cout << "The thing you tried to drop doesn't exist.\n\n";
		return false;
	}

	// Check if we can drop the item
	bool item_dropped = false;
	if (entity->entity_type == EntityType::BodyPart)
	{
		BodyPart* const body_part = dynamic_cast<BodyPart*>(entity);
		if (!body_part->is_attached)
		{
			// Severed body part
			body_part->ChangeParent(*location);

			std::cout << "You drop '" << body_part->name << "'.\n\n";
			item_dropped = true;
		}
		else
		{
			// Attached body part
			std::cout << "You can't drop '" << body_part->name << "'.\n\n";
		}
	}
	else if (entity->entity_type == EntityType::Pickable)
	{
		// Pickable
		Pickable* const pickable = dynamic_cast<Pickable*>(entity);
		pickable->ChangeParent(*location);

		std::cout << "You drop '" << pickable->name << "'.\n\n";
		item_dropped = true;
	}
	else
	{
		// Not a valid item
		std::cout << "You can't drop '" << entity->name << "'.\n\n";
	}

	return item_dropped;
}

bool Player::Put(const std::string & name, const std::string & container_name)
{
	Entity* const entity = RecursivelySearchEntity(contains, name);
	if (entity == nullptr)
	{
		// Unknown name
		std::cout << "The thing you tried to drop doesn't exist.\n\n";
		return false;
	}

	Entity* const container_entity = RecursivelySearchEntity(location->contains, container_name);
	if (container_entity == nullptr)
	{
		// Unknown name
		std::cout << "The object you tried to place the item in doesn't exist.\n\n";
		return false;
	}

	// Check if we can drop the item
	Item* selected_item = nullptr;
	if (entity->entity_type == EntityType::BodyPart)
	{
		BodyPart* const body_part = dynamic_cast<BodyPart*>(entity);
		if (!body_part->is_attached)
		{
			// Severed body part
			selected_item = body_part;
		}
	}
	else if (entity->entity_type == EntityType::Pickable)
	{
		// Pickable item
		selected_item = dynamic_cast<Item*>(entity);
	}
	if (selected_item == nullptr)
	{
		// Not a valid item to drop
		std::cout << "You can't drop '" << entity->name << "'.\n\n";
		return false;
	}

	// Check if we can put items in the given container
	bool item_moved = false;
	if (container_entity->entity_type == EntityType::Furniture || container_entity->entity_type == EntityType::Pickable)
	{
		Item* const container_item = dynamic_cast<Item*>(container_entity);
		if (container_item->is_container)
		{
			// Normal container
			selected_item->ChangeParent(*container_item);

			std::cout << "You put '" << selected_item->name << "' in '" << container_item->name << "'.\n\n";
			item_moved = true;
		}
		else
		{
			// Not a container
			std::cout << "You can't put '" << selected_item->name << "' in '" << container_item->name << "'.\n\n";
		}
	}
	else if (container_entity->entity_type == EntityType::BodyPart)
	{
		BodyPart* const container_body_part = dynamic_cast<BodyPart*>(container_entity);
		if (container_body_part->is_container)
		{
			if (CheckIsBodyPartEmpty(*container_body_part))
			{
				// Empty body part
				selected_item->ChangeParent(*container_body_part);

				std::cout << "You put '" << selected_item->name << "' in '" << container_body_part->name << "'.\n\n";
				item_moved = true;
			}
			else
			{
				// Full body part
				std::cout << "You can't put '" << selected_item->name << "' in '" << container_body_part->name << "'.\n\n";
			}
		}
		else
		{
			// Not a container
			std::cout << "You can't put '" << selected_item->name << "' in '" << container_body_part->name << "'.\n\n";
		}
	}
	else
	{
		// Not an item
		std::cout << "You can't put '" << selected_item->name << "' in '" << container_entity->name << "'.\n\n";
	}

	return item_moved;
}

void Damage(Entity* target, Item* source)
{
	target->health = std::max(0, target->health - source->damage);
	source->health = std::max(0, source->health - (source->damage / 2));
}

bool Player::Hit(const std::string& target_name, const std::string& source_name)
{
	Entity* const source_entity = RecursivelySearchEntity(contains, source_name);
	if (source_entity == nullptr)
	{
		std::cout << "The thing you tried to hit with doesn't exist.\n\n";
		return false;
	}

	Entity* const target_entity = RecursivelySearchEntity(location->contains, target_name);
	if (target_entity == nullptr)
	{
		std::cout << "The thing you tried to hit doesn't exist.\n\n";
		return false;
	}

	if (source_entity->entity_type != EntityType::BodyPart && source_entity->entity_type != EntityType::Pickable)
	{
		std::cout << "You can't use '" << source_entity->name << "' to hit anything.\n\n";
		return false;
	}

	// Damage the target
	Item* const source_item = dynamic_cast<Item*>(source_entity);
	if (target_entity->entity_type == EntityType::BodyPart)
	{
		BodyPart* const target_body_part = dynamic_cast<BodyPart*>(target_entity);
		if (!target_body_part->is_attached)
		{
			// Severed body part
			std::cout << "You hit '" << target_body_part->name << "' with '" << source_item->name << "'.\n\n";
			Damage(target_entity, source_item);
		}
		else
		{
			// Attached body part
			std::cout << "You hit '" << target_body_part->name << "' with '" << source_item->name << "'.\n\n";
			Damage(target_entity, source_item);
		}
	}
	else
	{
		// Other type of entity
		std::cout << "You hit '" << target_entity->name << "' with '" << source_item->name << "'.\n\n";
		Damage(target_entity, source_item);
	}

	return true;
}
