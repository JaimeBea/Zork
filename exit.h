#pragma once

#include "common.h"
#include "entity.h"

class World;
class Room;
class Item;

class Exit : public Entity
{
public:
	Exit(World& world, const std::string& name, const std::string& description, int health, Room& origin, Room& destination, Direction direction);
	~Exit();

	void Inspect() const override;

	Room* const origin;
	Room* const destination;
	const Direction direction;
};
