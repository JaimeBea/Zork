#pragma once

#include "common.h"
#include "creature.h"

class World;
class Room;

class Player : public Creature
{
public:
	Player
	(
		World& world,
		Room& location,
		const std::string& name,
		const std::string& description,
		int health,
		float damage_multiplier
	);

	void Damage(int damage) override;

	bool OnExamine(const std::string& name) const;
	bool OnGo(Direction direction);
	bool OnTake(const std::string& name);
	bool OnDrop(const std::string& name);
	bool OnPut(const std::string& name, const std::string& container_name);
	bool OnHit(const std::string& target_name, const std::string& source_name);
	bool OnOpen(const std::string& name);
};
