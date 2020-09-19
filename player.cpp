#include "player.h"
#include "room.h"
#include "exit.h"

Player::Player(World& world, const std::string& name, const std::string& description, Room& location) : Creature(world, EntityType::Player, name, description, location)
{
	location.Inspect();
}

bool RecursivelySearchEntities(const std::list<Entity*>& entities, const std::string& name)
{
	for (Entity* entity : entities)
	{
		if (CaseInsensitiveCompare(entity->name, name))
		{
			entity->Inspect();
			return true;
		}

		if (RecursivelySearchEntities(entity->contains, name))
		{
			return true;
		}
	}

	return false;
}

bool Player::Examine(const std::string& name)
{
	if (name == "")
	{ 
		location->Inspect();
		return true;
	}
	else
	{
		std::vector<std::string> entity_name_tokens;

		if (RecursivelySearchEntities(location->contains, name))
		{
			return true;
		}
	}

	return false;
}

bool Player::Go(Direction direction)
{
	Exit* exit = location->GetExit(direction);
	if (exit == nullptr)
	{
		std::cout << "You can't go " << GetDirectionName(direction) << "\n\n";
		return false;
	}

	Room* target;
	if (&exit->origin == location)
	{
		target = &exit->destination;
	}
	else
	{
		target = &exit->origin;
	}
	location->contains.remove(this);
	location = target;
	target->contains.push_back(this);

	target->Inspect();

	return true;
}
