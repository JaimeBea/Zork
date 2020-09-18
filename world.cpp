#include "world.h"
#include "room.h"
#include "exit.h"
#include "player.h"

World::World()
{
	// Rooms

	Room* cell = new Room(*this, "Player Cell", "You find yourself inside a very small cell. There is a bed tucked in the corner.");
	Room* corridor = new Room(*this, "Jail Corridor", "The corridor extends to the east and west. There are cells to the north and south.");
	Room* other_cell = new Room(*this, "Empty Cell", "The cell is very similar to the other one. The bed is broken and a plank with nails rests on the ground.");
	Room* arena_lounge = new Room(*this, "Arena Lounge", "You find yourself at the arena lounge. You can see the light coming from the arena.");
	Room* office = new Room(*this, "Office", "You are in your slavemaster Porcius' office. Porcius is distracted looking at some documents away from the door.");
	Room* arena = new Room(*this, "Arena", "The arena is filled with sand and blood stains. The public cheers for Kroz, who is smirking at you.");

	// Exits

	Exit* cell_exit = new Exit(*this, "Player Cell Door", "Door made of vertical metal bars.", *cell, *corridor, Direction::North);
	Exit* other_cell_exit = new Exit(*this, "Empty Cell Door", "Door made of vertical metal bars.", *other_cell, *corridor, Direction::South);
	Exit* arena_lounge_corridor_exit = new Exit(*this, "Lounge Door", "Simple wooden door.", *arena_lounge, *corridor, Direction::East);
	Exit* office_exit = new Exit(*this, "Office Door", "Simple wooden door.", *office, *corridor, Direction::West);
	Exit* arena_lounge_arena_exit = new Exit(*this, "Arena Entrance", "Big open wooden door.", *arena_lounge, *arena, Direction::North);

	// Player

	player = new Player(*this, "Player", "You look fine.", *cell);
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
			std::cout << "Commands:\n";
			std::cout << "  help           - Shows this information.\n";
			std::cout << "  examine [object] - Examine something. If written with no arguments it examines the current room.\n";
			std::cout << "  go <direction> - Move towards a direction.\n";
			std::cout << "\n";
			std::cout << "Objects:\n";
			std::cout << "  Everything inside the room or inside the objects of the room counts as an object.\n";
			std::cout << "  You have to be explicit when giving the name of an object or it won't be recognized.\n";
			std::cout << "\n";
			std::cout << "Directions:\n";
			std::cout << "  The only accepted directions are north, south, east and west.\n";
			std::cout << "\n";
			return false;
		}
		else if (tokens[0] == "examine")
		{
			if (player->Examine(tokens))
			{
				return false;
			}
			else
			{
				std::cout << "The thing you tried to examine doesn't exist.\n\n";
				return false;
			}
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
