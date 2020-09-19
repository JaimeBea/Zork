#pragma once

#include "common.h"
#include "creature.h"

class Room;

class Player : public Creature
{
public:
	Player(World& world, Room& location, const std::string& name, const std::string& description);

	bool Examine(const std::string& name) const;
	bool Go(Direction direction);
	bool Take(const std::string& name);
	bool Drop(const std::string& name);
	bool Put(const std::string& name, const std::string& container_name);
};
