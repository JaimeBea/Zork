#pragma once

#include "common.h"
#include "creature.h"

class World;
class Room;

class NPC : public Creature
{
public:
	NPC(World& world, Room& location, const std::string& name, const std::string& description, int health);
};
