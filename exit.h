#pragma once

#include "common.h"
#include "entity.h"

class World;
class Room;
class Item;

class Exit : public Entity
{
public:
	Exit
	(
		World& world,
		const std::string& name,
		const std::string& description,
		int health,
		Room& origin,
		Room& destination,
		Direction direction,
		Item* key
	);
	~Exit();

	void Inspect() const override;

	Room* origin;
	Room* destination;
	Direction direction;
};
