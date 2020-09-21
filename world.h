#pragma once

#include "common.h"

class Entity;
class Player;
class NPC;

class World
{
public:
	World();
	~World();

	bool Tick(const std::vector<std::string>& tokens);

	std::vector<Entity*> entities;
	Player* player;
	NPC* kroz;

private:
	bool ParseCommand(const std::vector<std::string>& tokens);
};

