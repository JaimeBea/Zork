#include "player.h"
#include "room.h"
#include "exit.h"
#include "item.h"

Player::Player(World& world, const std::string& name, const std::string& description, Room& location) : Creature(world, EntityType::Player, name, description, location)
{
	location.Inspect();
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
				// Search for an empty body part to put the item in
				Item* empty_body_part = nullptr;
				for (Entity* const entity : contains)
				{
					if (entity->entity_type != EntityType::Item) continue;

					Item* const body_part = dynamic_cast<Item*>(entity);
					if (body_part->is_container && body_part->contains.empty())
					{
						empty_body_part = body_part;
					}
				}

				// Put the item in the found body part
				if (empty_body_part != nullptr)
				{
					item->ChangeParent(*empty_body_part);

					std::cout << "You take '" << item->name << "'.\n\n";
					return true;
				}
				else
				{
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
					if (container_entity->contains.empty())
					{
						// Empty body part
						selected_item->ChangeParent(*container_entity);

						std::cout << "You put '" << selected_item->name << "' in '" << container_entity->name << "'.\n\n";
						return true;
					}
					else
					{
						// Full body part
						std::cout << "You can't put '" << selected_item->name << "' in '" << container_entity->name << "'.\n\n";
						return false;
					}
				}
				else
				{
					// Normal container
					selected_item->ChangeParent(*container_entity);

					std::cout << "You put '" << selected_item->name << "' in '" << container_entity->name << "'.\n\n";
					return true;
				}
			}
			else
			{
				// Not a container
				std::cout << "You can't put '" << selected_item->name << "' in '" << container_entity->name << "'.\n\n";
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
