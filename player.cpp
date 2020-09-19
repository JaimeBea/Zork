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

				std::cout << "You take the '" << item->name << "'.\n\n";
				return true;
			}
			else
			{
				std::cout << "The '" << item->name << "' is too big to be picked up.\n\n";
				return false;
			}
		}
		else
		{
			std::cout << "You can't pick up '" << entity->name << "'.\n\n";
			return false;
		}
	}

	return false;
}
