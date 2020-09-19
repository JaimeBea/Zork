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
	const Exit* const exit = location->GetExit(direction);
	if (exit == nullptr)
	{
		std::cout << "You can't go " << GetDirectionName(direction) << "\n\n";
		return false;
	}

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

	target->Inspect();

	return true;
}

bool Player::Take(const std::string& name)
{
	Entity* const entity = RecursivelySearchEntity(location->contains, name);
	if (entity != nullptr)
	{
		if (entity->entity_type == EntityType::Item)
		{
			Item* item = dynamic_cast<Item*>(entity);
			if (item->item_type == ItemType::Object)
			{
				item->ChangeParent(*this);

				std::cout << "You take '" << item->name << "'.\n\n";
				return true;
			}
			else
			{
				std::cout << "You can't pick up '" << item->name << "'.\n\n";
				return false;
			}
		}
		else
		{
			std::cout << "You can't pick up '" << entity->name << "'.\n\n";
			return false;
		}
	}

	std::cout << "The thing you tried to take doesn't exist.\n\n";
	return false;
}

bool Player::Drop(const std::string& name)
{
	Entity* const entity = RecursivelySearchEntity(contains, name);
	if (entity != nullptr)
	{
		if (entity->entity_type == EntityType::Item)
		{
			Item* item = dynamic_cast<Item*>(entity);
			if (item->item_type == ItemType::Object)
			{
				item->ChangeParent(*location);

				std::cout << "You drop '" << item->name << "'.\n\n";
				return true;
			}
			else
			{
				std::cout << "You can't drop '" << item->name << "'.\n\n";
				return false;
			}
		}
		else
		{
			std::cout << "You can't drop '" << entity->name << "'.\n\n";
			return false;
		}
	}

	std::cout << "The thing you tried to drop doesn't exist.\n\n";
	return false;
}

bool Player::Put(const std::string & name, const std::string & container_name)
{
	Item* item = nullptr;
	Entity* const entity = RecursivelySearchEntity(contains, name);
	if (entity != nullptr)
	{
		if (entity->entity_type == EntityType::Item)
		{
			item = dynamic_cast<Item*>(entity);
			if (item->item_type != ItemType::Object)
			{
				std::cout << "You can't drop '" << item->name << "'.\n\n";
				return false;
			}
		}
		else
		{
			std::cout << "You can't drop '" << entity->name << "'.\n\n";
			return false;
		}
	}
	else
	{
		std::cout << "The thing you tried to drop doesn't exist.\n\n";
		return false;
	}

	// 'item' will always be set by this point

	Entity* const container_entity = RecursivelySearchEntity(location->contains, container_name);
	if (container_entity != nullptr)
	{
		item->ChangeParent(*container_entity);

		std::cout << "You put '" << item->name << "' in '" << container_entity->name << "'.\n\n";
		return true;
	}
	else
	{
		std::cout << "The object you tried to place the item in doesn't exist.\n\n";
		return false;
	}
}
