#include "world.h"
#include "room.h"
#include "exit.h"
#include "player.h"
#include "item.h"

World::World()
{
	// Rooms

	Room* cell = new Room(*this, "Player Cell", "You find yourself inside a very small cell. There is a bed tucked in the corner.");
	Item* player_bed = new Item(*this, *cell, ItemType::Furniture, "Bed", "Your bed. It's a simple wooden bed with very little padding.");
	Item* letter = new Item(*this, *player_bed, ItemType::Object, "Letter", "\"I'll be waiting outside for you. Hurry up and win the fight!\"\n - Amor");

	Room* corridor = new Room(*this, "Jail Corridor", "The corridor extends to the east and west. There are cells to the north and south.");

	Room* other_cell = new Room(*this, "Empty Cell", "The cell is very similar to the other one. The bed is broken and a plank with nails rests on the ground.");
	Item* broken_bed = new Item(*this, *other_cell, ItemType::Furniture, "Broken bed", "The remains of a wooden bed. Looks like a heavy fight happened.");
	Item* board_with_nails = new Item(*this, *broken_bed, ItemType::Object, "Board With Nails", "This board broke off from the broken bed.");

	Room* arena_lounge = new Room(*this, "Arena Lounge", "You find yourself at the arena lounge. You can see the light coming from the arena.");
	Item* banana_peel = new Item(*this, *arena_lounge, ItemType::Object, "Banana Peel", "A banana peel.");

	Room* office = new Room(*this, "Office", "You are in your slavemaster Porcius' office. Porcius is distracted looking at some documents away from the door.");
	Item* desk = new Item(*this, *office, ItemType::Furniture, "Desk", "A wooden desk. There are multiple drawers.");
	Item* armory_key = new Item(*this, *desk, ItemType::Object, "Armory Key", "The key that opens the armory door.");

	Room* armory = new Room(*this, "Armory", "The armory is enormous. There are a lot of weapons to pick from.");
	Item* sword = new Item(*this, *armory, ItemType::Object, "Sword", "Metal sword.");
	Item* mace = new Item(*this, *armory, ItemType::Object, "Mace", "Metal mace.");
	Item* spear = new Item(*this, *armory, ItemType::Object, "Spear", "Metal spear.");
	Item* shield = new Item(*this, *armory, ItemType::Object, "Shield", "Metal shield.");

	Room* arena = new Room(*this, "Arena", "The arena is filled with sand and blood stains. The public cheers for Kroz, who is smirking at you.");

	// Exits

	Exit* cell_exit = new Exit(*this, "Player Cell Door", "Door made of vertical metal bars.", *cell, *corridor, Direction::North);
	Exit* other_cell_exit = new Exit(*this, "Empty Cell Door", "Door made of vertical metal bars.", *other_cell, *corridor, Direction::South);
	Exit* arena_lounge_corridor_exit = new Exit(*this, "Lounge Door", "Simple wooden door.", *arena_lounge, *corridor, Direction::East);
	Exit* office_exit = new Exit(*this, "Office Door", "Simple wooden door.", *office, *corridor, Direction::West);
	Exit* armory_exit = new Exit(*this, "Armory Door", "Full metal door with a keylock.", *armory, *arena_lounge, Direction::North);
	Exit* arena_lounge_arena_exit = new Exit(*this, "Arena Entrance", "Very large wooden door.", *arena_lounge, *arena, Direction::North);

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
			std::string name = JoinTokens(tokens, 1, tokens.size());

			if (player->Examine(name))
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
