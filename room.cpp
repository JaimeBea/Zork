#include "room.h"
#include "exit.h"

Room::Room(World& world, const std::string& name, const std::string& description)
	: Entity(world, EntityType::Room, name, description, -1, nullptr) {}

void Room::Inspect() const
{
	Entity::Inspect();

	if (!contains.empty())
	{
		std::cout << "Contains:\n";
		for (const Entity* const entity : contains)
		{
			if (entity->entity_type == EntityType::Exit) continue;

			std::cout << "  " << entity->name << "\n";
		}

		std::cout << "Exits:\n";
		for (const Entity* const entity : contains)
		{
			if (entity->entity_type != EntityType::Exit) continue;
			const Exit* const exit = dynamic_cast<const Exit*>(entity);

			const Direction exit_direction = exit->origin == this ? exit->direction : GetOppositeDirection(exit->direction);
			std::cout << "  (" << GetDirectionName(exit_direction) << ") " << exit->name << "\n";
		}
	}
}

Exit* Room::GetExit(Direction direction) const
{
	for (Entity* const entity : contains)
	{
		if (entity->entity_type != EntityType::Exit)
		{
			// Not an exit
			continue;
		}

		Exit* const exit = dynamic_cast<Exit*>(entity);
		if (exit->origin == this && exit->direction == direction)
		{
			return exit;
		}
		else if (exit->destination == this && GetOppositeDirection(exit->direction) == direction)
		{
			return exit;
		}
	}

	return nullptr;
}

Room* Room::GetExitRoom(Direction direction) const
{
	for (Entity* const entity : contains)
	{
		if (entity->entity_type != EntityType::Exit)
		{
			// Not an exit
			continue;
		}

		Exit* const exit = dynamic_cast<Exit*>(entity);
		if (exit->origin == this && exit->direction == direction)
		{
			return exit->destination;
		}
		else if (exit->destination == this && GetOppositeDirection(exit->direction) == direction)
		{
			return exit->origin;
		}
	}

	return nullptr;
}
