#include "exit.h"
#include "room.h"

Exit::Exit(World& world, const char* name, const char* description, Room& origin, Room& destination, Direction direction) : Entity(world, EntityType::Exit, name, description), origin(origin), destination(destination), direction(direction)
{
	origin.contains.push_back(this);
	destination.contains.push_back(this);
}

Exit::~Exit()
{
	origin.contains.remove(this);
	destination.contains.remove(this);
}
