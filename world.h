#pragma once

#include "common.h"
#include "entity.h"

class World
{
public:
	World();
	~World();

	void Tick(const std::vector<std::string>& tokens);

private:
	std::vector<Entity*> entities;
};

