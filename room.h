#pragma once

#include "common.h"
#include "entity.h"

class Exit;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);

	Exit* GetExit(const Direction direction) const;
};
