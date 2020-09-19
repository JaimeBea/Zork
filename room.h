#pragma once

#include "common.h"
#include "entity.h"

class Exit;

class Room : public Entity
{
public:
	Room(World& world, const std::string& name, const std::string& description);

	void Inspect() const override;

	Exit* GetExit(Direction direction) const;
	Room* GetExitRoom(Direction direction) const;
};
