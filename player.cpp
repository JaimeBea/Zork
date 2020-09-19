#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"

Player::Player(World& world, Room& location, const std::string& name, const std::string& description) : Creature(world, location, EntityType::Player, name, description)
{
	location.Inspect();
}

bool CheckIsBodyPartEmpty(const Item& body_part)
{
	for (const Entity* const entity : body_part.contains)
	{
		if (entity->entity_type != EntityType::Item) continue;

		const Item* const item = dynamic_cast<const Item*>(entity);

		if (!item->is_attached)
		{
			// We found an item that's not a body part
			return false;
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

Item* RecursivelySearchEmptyBodyPart(const Entity& parent)
{
	for (Entity* const entity : parent.contains)
	{
		if (entity->entity_type != EntityType::Item) continue;

		Item* const item = dynamic_cast<Item*>(entity);

		if (item->is_attached)
		{
			if (item->is_container)
			{
				if (CheckIsBodyPartEmpty(*item))
				{
					return item;
				}
			}
			else
			{
				Item* const found_empty_body_part = RecursivelySearchEmptyBodyPart(*item);
				if (found_empty_body_part != nullptr)
				{
					return found_empty_body_part;
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
	// Check if we can take the item
	Entity* const entity = RecursivelySearchEntity(location->contains, name);
	if (entity != nullptr)
	{
		if (entity->entity_type == EntityType::Item)
		{
			Item* const item = dynamic_cast<Item*>(entity);
			if (!item->is_attached)
			{
				Item* const empty_body_part = RecursivelySearchEmptyBodyPart(*this);
				if (empty_body_part != nullptr)
				{
					// Empty body part found
					item->ChangeParent(*empty_body_part);

					std::cout << "You take '" << item->name << "'.\n\n";
					return true;
				}
				else
				{
					// No empty body part found
					std::cout << "You have no empty hands.\n\n";
					return false;
				}
			}
			else
			{
				// The item is a body part
				std::cout << "You can't pick up '" << item->name << "'.\n\n";
				return false;
			}
		}
		else
		{
			// Not an item
			std::cout << "You can't pick up '" << entity->name << "'.\n\n";
			return false;
		}
	}

	// Unknown name
	std::cout << "The thing you tried to take doesn't exist.\n\n";
	return false;
}

bool Player::Drop(const std::string& name)
{
	// Check if we can drop the item
	Entity* const entity = RecursivelySearchEntity(contains, name);
	if (entity != nullptr)
	{
		if (entity->entity_type == EntityType::Item)
		{
			Item* const item = dynamic_cast<Item*>(entity);
			if (!item->is_attached)
			{
				// Normal item
				item->ChangeParent(*location);

				std::cout << "You drop '" << item->name << "'.\n\n";
				return true;
			}
			else
			{
				// Body part
				std::cout << "You can't drop '" << item->name << "'.\n\n";
				return false;
			}
		}
		else
		{
			// Not an item
			std::cout << "You can't drop '" << entity->name << "'.\n\n";
			return false;
		}
	}

	std::cout << "The thing you tried to drop doesn't exist.\n\n";
	return false;
}

bool Player::Put(const std::string & name, const std::string & container_name)
{
	// Check if we can drop the item
	Item* selected_item = nullptr;
	Entity* const entity = RecursivelySearchEntity(contains, name);
	if (entity != nullptr)
	{
		if (entity->entity_type == EntityType::Item)
		{
			Item* const item = dynamic_cast<Item*>(entity);
			if (!item->is_attached)
			{
				// Normal item
				selected_item = item;
			}
			else
			{
				// Body part
				std::cout << "You can't drop '" << item->name << "'.\n\n";
				return false;
			}
		}
		else
		{
			// Not an item
			std::cout << "You can't drop '" << entity->name << "'.\n\n";
			return false;
		}
	}
	else
	{
		// Unknown name
		std::cout << "The thing you tried to drop doesn't exist.\n\n";
		return false;
	}

	// Check if we can put items in the given container
	Entity* const container_entity = RecursivelySearchEntity(location->contains, container_name);
	if (container_entity != nullptr)
	{
		if (container_entity->entity_type == EntityType::Item)
		{
			Item* const container_item = dynamic_cast<Item*>(container_entity);
			if (container_item->is_container)
			{
				if (container_item->is_attached)
				{
					if (CheckIsBodyPartEmpty(*container_item))
					{
						// Empty body part
						selected_item->ChangeParent(*container_item);

						std::cout << "You put '" << selected_item->name << "' in '" << container_item->name << "'.\n\n";
						return true;
					}
					else
					{
						// Full body part
						std::cout << "You can't put '" << selected_item->name << "' in '" << container_item->name << "'.\n\n";
						return false;
					}
				}
				else
				{
					// Normal container
					selected_item->ChangeParent(*container_item);

					std::cout << "You put '" << selected_item->name << "' in '" << container_item->name << "'.\n\n";
					return true;
				}
			}
			else
			{
				// Not a container
				std::cout << "You can't put '" << selected_item->name << "' in '" << container_item->name << "'.\n\n";
				return false;
			}
		}
		else
		{
			// Not an item
			std::cout << "You can't put '" << selected_item->name << "' in '" << container_entity->name << "'.\n\n";
			return false;
		}
	}
	else
	{
		// Unknown name
		std::cout << "The object you tried to place the item in doesn't exist.\n\n";
		return false;
	}
}
