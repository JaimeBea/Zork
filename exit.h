#pragma once

#include "common.h"
#include "entity.h"

class Room;

class Exit : public Entity
{
public:
	Exit(const char* name, const char* description, const Room& origin, const Room& destination, const Direction direction);

	const Room& origin;
	const Room& destination;
	const Direction direction;
};
