#include "exit.h"
#include "room.h"

Exit::Exit(World& world, const std::string& name, const std::string& description, int health, Room& origin, Room& destination, Direction direction)
	: Entity(world, EntityType::Exit, name, description, health), origin(&origin), destination(&destination), direction(direction)
{
	origin.contains.push_back(this);
	destination.contains.push_back(this);
}

Exit::~Exit()
{
	origin->contains.remove(this);
	destination->contains.remove(this);
}

void Exit::Inspect() const
{
	Entity::Inspect();

	if (health == 0)
	{
		std::cout << "It's broken.\n\n";
	}

	std::cout << "Connects:\n";
	std::cout << "  " << origin->name << " (" << GetDirectionName(GetOppositeDirection(direction)) << ")\n";
	std::cout << "  " << destination->name << " (" << GetDirectionName(direction) << ")\n";
	std::cout << "\n";
}
