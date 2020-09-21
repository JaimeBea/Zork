#pragma once

#include "common.h"
#include "creature.h"

class World;
class Room;

enum class NPCType
{
	Kroz,
	Porcius
};

class NPC : public Creature
{
public:
	NPC(World& world, Room& location, NPCType npc_type, const std::string& name, const std::string& description, int health);

	void Update() override;
	void Damage(int damage) override;

	NPCType npc_type;
};
