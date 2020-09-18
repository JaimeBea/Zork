#include "room.h"
#include "exit.h"

Room::Room(World& world, const char* name, const char* description) : Entity(world, EntityType::Room, name, description)
{

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
