#include "exit.h"

Exit::Exit(const char* name, const char* description, const Room& origin, const Room& destination, const Direction direction) : Entity(EntityType::Exit, name, description), origin(origin), destination(destination), direction(direction)
{

}
