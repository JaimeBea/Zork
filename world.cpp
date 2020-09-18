#include "world.h"
#include "room.h"
#include "exit.h"
#include "player.h"

World::World()
{
	// Rooms

	Room* cell = new Room(*this, "Cell", "You find yourself inside a very small cell. There is a bed tucked in the corner.");
	Room* corridor = new Room(*this, "Jail Corridor", "The corridor extends to the east and west. There are cells to the north and south.");
	Room* other_cell = new Room(*this, "Cell", "The cell is very similar to the other one. The bed is broken and a plank with nails rests on the ground.");
	Room* arena_lounge = new Room(*this, "Arena Lounge", "You find yourself at the arena lounge. You can see the light coming from the arena.");
	Room* office = new Room(*this, "Office", "You are in your slavemaster Porcius's office. Porcius is distracted looking at some documents away from the door.");
	Room* arena = new Room(*this, "Arena", "The arena is filled with sand and blood stains. The public cheers for Kroz, who is smirking at you.");

	// Exits

	Exit* cell_exit = new Exit(*this, "Jail Door", "Metal door made of vertical bars.", *cell, *corridor, Direction::North);
	Exit* other_cell_exit = new Exit(*this, "Jail Door", "Metal door made of vertical bars.", *other_cell, *corridor, Direction::South);
	Exit* arena_lounge_corridor_exit = new Exit(*this, "Lounge Door", "This door takes you to the lounge.", *arena_lounge, *corridor, Direction::East);
	Exit* office_exit = new Exit(*this, "Latrines Door", "This door takes you to the latrines.", *office, *corridor, Direction::West);
	Exit* arena_lounge_arena_exit = new Exit(*this, "Arena Entrance", "You can see light on the other side.", *arena_lounge, *arena, Direction::North);

	// Player

	player = new Player(*this, "You", "You look fine.", *cell);
}

World::~World()
{
	for (Entity* entity : entities)
	{
		delete entity;
	}

	entities.clear();
}

void World::Tick(const std::vector<std::string>& tokens)
{
	bool action_executed = ParseCommand(tokens);
}

bool World::ParseCommand(const std::vector<std::string>& tokens)
{
	if (tokens.size() >= 1) {
		if (tokens[0] == "help")
		{
			std::cout << "Commands:\nhelp - Shows this information.\ngo <direction> - Move towards a direction.\n\n";
			return false;
		}
		else if (tokens[0] == "go")
		{
			Direction direction = GetDirectionFromName(tokens[1]);
			if (direction != Direction::Unknown)
			{
				return player->Go(direction);
			}
		}
	}

	std::cout << "I didn't understand what you wanted to do. Write 'help' to view the possible commands.\n\n";
	return false;
}
