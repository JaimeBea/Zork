#pragma once

#include "common.h"
#include "creature.h"

class World;
class Room;

class Player : public Creature
{
public:
	Player(World& world, Room& location, const std::string& name, const std::string& description, int health);

	bool Examine(const std::string& name) const;
	bool Go(Direction direction);
	bool Take(const std::string& name);
	bool Drop(const std::string& name);
	bool Put(const std::string& name, const std::string& container_name);
	bool Hit(const std::string& target_name, const std::string& source_name);
};
