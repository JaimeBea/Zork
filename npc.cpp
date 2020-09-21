#include "npc.h"

NPC::NPC(World& world, Room& location, const std::string& name, const std::string& description, int health)
	: Creature(world, location, EntityType::NPC, name, description, health) {}

void NPC::Damage(int damage)
{
	const int previous_health = health;

	Creature::Damage(damage);

	if (health == 0)
	{
		if (previous_health != 0)
		{
			std::cout << "'" << name << " dies and falls to the ground face first.\n";
		}
		else
		{
			std::cout << "'" << name << " is already dead.\n";
		}
	}
}
