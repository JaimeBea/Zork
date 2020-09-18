#pragma once

#include "common.h"
#include "entity.h"

class Player;

class World
{
public:
	World();
	~World();

	void Tick(const std::vector<std::string>& tokens);

	std::vector<Entity*> entities;
	Player* player;

private:
	bool ParseCommand(const std::vector<std::string>& tokens);
};

