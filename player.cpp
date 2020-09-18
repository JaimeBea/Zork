#include "player.h"
#include "room.h"
#include "exit.h"

Player::Player(World& world, const char* name, const char* description, Room& location) : Creature(world, EntityType::Player, name, description, location)
{
	std::cout << location.description << "\n\n";
}

bool Player::Go(Direction direction)
{
	Exit* exit = location->GetExit(direction);
	if (exit == nullptr)
	{
		const char* direction_name = GetDirectionName(direction);
		std::cout << "You can't go " << direction_name << "\n\n";
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

	std::cout << target->description << "\n\n";

	return true;
}
