#include "exit.h"
#include "room.h"

Exit::Exit(World& world, const std::string& name, const std::string& description, Room& origin, Room& destination, Direction direction) : Entity(world, EntityType::Exit, name, description), origin(&origin), destination(&destination), direction(direction)
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
	std::cout << name << ":\n";
	std::cout << description << "\n\n";

	std::cout << "Connects:\n";
	std::cout << "  " << origin->name << " (" << GetDirectionName(GetOppositeDirection(direction)) << ")\n";
	std::cout << "  " << destination->name << " (" << GetDirectionName(direction) << ")\n";
	std::cout << "\n";
}
