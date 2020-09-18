#pragma once

#include "common.h"
#include "entity.h"

class Room;

class Exit : public Entity
{
public:
	Exit(World& world, std::string name, std::string description, Room& origin, Room& destination, Direction direction);
	~Exit();

	void Inspect() const override;

	Room& origin;
	Room& destination;
	Direction direction;
};
