#include "room.h"
#include "exit.h"

Room::Room(World& world, std::string name, std::string description) : Entity(world, EntityType::Room, name, description) {}

void Room::Inspect() const
{
	std::cout << name << ":\n";
	std::cout << description << "\n\n";

	if (!contains.empty())
	{
		std::cout << "Contains:\n";
		for (Entity* entity : contains)
		{
			if (entity->type == EntityType::Exit) continue;

			std::cout << "  " << entity->name << "\n";
		}
		std::cout << "\n";

		std::cout << "Exits:\n";
		for (Entity* entity : contains)
		{
			if (entity->type != EntityType::Exit) continue;
			const Exit* exit = (Exit*)entity;

			Direction exit_direction = &exit->origin == this ? exit->direction : GetOppositeDirection(exit->direction);
			std::cout << "  (" << GetDirectionName(exit_direction) << ") " << exit->name << "\n";
		}
		std::cout << "\n";
	}
}

Exit* Room::GetExit(Direction direction) const
{
	for (const Entity* entity : contains)
	{
		if (entity->type == EntityType::Exit)
		{
			Exit* exit = (Exit*) entity;
			if (&exit->origin == this && exit->direction == direction)
			{
				return exit;
			}
			else if (&exit->destination == this && GetOppositeDirection(exit->direction) == direction)
			{
				return exit;
			}
		}
	}

	return nullptr;
}

Room* Room::GetExitRoom(Direction direction) const
{
	for (const Entity* entity : contains)
	{
		if (entity->type == EntityType::Exit)
		{
			Exit* exit = (Exit*)entity;
			if (&exit->origin == this && exit->direction == direction)
			{
				return &exit->destination;
			}
			else if (&exit->destination == this && GetOppositeDirection(exit->direction) == direction)
			{
				return &exit->origin;
			}
		}
	}

	return nullptr;
}
