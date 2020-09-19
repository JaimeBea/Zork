#include "world.h"
#include "room.h"
#include "exit.h"
#include "player.h"
#include "npc.h"
#include "item.h"

World::World()
{
	// Rooms

	Room* const cell = new Room(*this, "Player Cell", "You find yourself inside a very small cell. There is a bed tucked in the corner.");
	Item* const player_bed = new Item(*this, *cell, "Bed", "Your bed. It's a simple wooden bed with very little padding.", true, true, false);
	Item* const envelope = new Item(*this, *player_bed, "Envelope", "A letter envelope.", true, false, false);
	Item* const letter = new Item(*this, *envelope, "Letter", "\"I'll be waiting outside for you. Hurry up and win the fight!\"\n - Amor", false, false, false);

	Room* const corridor = new Room(*this, "Jail Corridor", "The corridor extends to the east and west. There are cells to the north and south.");

	Room* const other_cell = new Room(*this, "Empty Cell", "The cell is very similar to the other one. The bed is broken and a plank with nails rests on the ground.");
	Item* const broken_bed = new Item(*this, *other_cell, "Broken bed", "The remains of a wooden bed. Looks like a heavy fight happened.", true, true, false);
	Item* const board = new Item(*this, *broken_bed, "Board", "This board broke off from the broken bed.", false, false, false);

	Room* const arena_lounge = new Room(*this, "Arena Lounge", "You find yourself at the arena lounge. You can see the light coming from the arena.");
	Item* const banana_peel = new Item(*this, *arena_lounge, "Banana Peel", "A banana peel.", false, false, false);

	Room* const office = new Room(*this, "Office", "You are in your slavemaster Porcius' office. Porcius is distracted looking at some documents away from the door.");
	NPC* const porcius = new NPC(*this, *office, "Porcius", "Your slavemaster is extremely fat and ugly. His face resembles a pig.");
	Item* const porcius_head = new Item(*this, *porcius, "Porcius Head", "Porcius' head.", false, false, true);
	Item* const porcius_right_eye = new Item(*this, *porcius_head, "Porcius Right Eye", "Porcius' right eye.", false, false, true);
	Item* const porcius_left_eye = new Item(*this, *porcius_head, "Porcius Left Eye", "Porcius' left eye.", false, false, true);
	Item* const porcius_right_arm = new Item(*this, *porcius, "Porcius Right Arm", "Porcius' right arm.", false, false, true);
	Item* const porcius_right_hand = new Item(*this, *porcius_right_arm, "Porcius Right Hand", "Porcius' right hand.", true, false, true);
	Item* const porcius_left_arm = new Item(*this, *porcius, "Porcius Left Arm", "Porcius' left arm.", false, false, true);
	Item* const porcius_left_hand = new Item(*this, *porcius_left_arm, "Porcius Left Hand", "Porcius' left hand.", true, false, true);
	Item* const porcius_right_leg = new Item(*this, *porcius, "Porcius Right Leg", "Porcius' right leg.", false, false, true);
	Item* const porcius_right_foot = new Item(*this, *porcius_right_leg, "Porcius Right Foot", "Porcius' right foot.", false, false, true);
	Item* const porcius_left_leg = new Item(*this, *porcius, "Porcius Left Leg", "Porcius' left leg.", false, false, true);
	Item* const porcius_left_foot = new Item(*this, *porcius_left_leg, "Porcius Left Foot", "Porcius' left foot.", false, false, true);
	Item* const dagger = new Item(*this, *porcius_right_arm, "Dagger", "Porcius' dagger. It's decorated with gems of multiple colors.", false, false, false);
	Item* const desk_key = new Item(*this, *porcius_right_leg, "Desk Key", "It opens the desk in Porcius' office.", false, false, false);
	Item* const desk = new Item(*this, *office, "Desk", "A wooden desk. There are multiple drawers.", true, true, false);
	Item* const armory_key = new Item(*this, *desk, "Armory Key", "The key that opens the armory door.", false, false, false);

	Room* const armory = new Room(*this, "Armory", "The armory is enormous. There are a lot of weapons to pick from.");
	Item* const sword = new Item(*this, *armory, "Sword", "Metal sword.", false, false, false);
	Item* const mace = new Item(*this, *armory, "Mace", "Metal mace.", false, false, false);
	Item* const spear = new Item(*this, *armory, "Spear", "Metal spear.", false, false, false);
	Item* const shield = new Item(*this, *armory, "Shield", "Metal shield.", false, false, false);

	Room* const arena = new Room(*this, "Arena", "The arena is filled with sand and blood stains. The public cheers for Kroz, who is smirking at you.");
	NPC* const kroz = new NPC(*this, *arena, "Kroz", "He's about two heads taller than you. You can feel a great sense of danger.");
	Item* const kroz_head = new Item(*this, *kroz, "Kroz Head", "Kroz's head.", false, false, true);
	Item* const kroz_right_eye = new Item(*this, *kroz_head, "Kroz Right Eye", "Kroz's right eye.", false, false, true);
	Item* const kroz_left_eye = new Item(*this, *kroz_head, "Kroz Left Eye", "Kroz's left eye.", false, false, true);
	Item* const kroz_right_arm = new Item(*this, *kroz, "Kroz Right Arm", "Kroz's right arm.", false, false, true);
	Item* const kroz_right_hand = new Item(*this, *kroz_right_arm, "Kroz Right Hand", "Kroz's right hand.", true, false, true);
	Item* const kroz_left_arm = new Item(*this, *kroz, "Kroz Left Arm", "Kroz's left arm.", false, false, true);
	Item* const kroz_left_hand = new Item(*this, *kroz_left_arm, "Kroz Left Hand", "Kroz's left hand.", true, false, true);
	Item* const kroz_right_leg = new Item(*this, *kroz, "Kroz Right Leg", "Kroz's right leg.", false, false, true);
	Item* const kroz_right_foot = new Item(*this, *kroz_right_leg, "Kroz Right Foot", "Kroz's right foot.", false, false, true);
	Item* const kroz_left_leg = new Item(*this, *kroz, "Kroz Left Leg", "Kroz's left leg.", false, false, true);
	Item* const kroz_left_foot = new Item(*this, *kroz_left_leg, "Kroz Left Foot", "Kroz's left foot.", false, false, true);
	Item* const axe = new Item(*this, *kroz_right_hand, "Axe", "Kroz's Axe. It's taller than you.", false, false, false);
	Item* const morning_star = new Item(*this, *kroz_left_hand, "Morning Star", "Kroz's Morning Star. A huge metal mace with spikes.", false, false, false);

	// Exits

	Exit* const cell_exit = new Exit(*this, "Player Cell Door", "Door made of vertical metal bars.", *cell, *corridor, Direction::North);
	Exit* const other_cell_exit = new Exit(*this, "Empty Cell Door", "Door made of vertical metal bars.", *other_cell, *corridor, Direction::South);
	Exit* const arena_lounge_corridor_exit = new Exit(*this, "Lounge Door", "Simple wooden door.", *arena_lounge, *corridor, Direction::East);
	Exit* const office_exit = new Exit(*this, "Office Door", "Simple wooden door.", *office, *corridor, Direction::West);
	Exit* const armory_exit = new Exit(*this, "Armory Door", "Full metal door with a keylock.", *armory, *arena_lounge, Direction::North);
	Exit* const arena_lounge_arena_exit = new Exit(*this, "Arena Entrance", "Very large wooden door.", *arena_lounge, *arena, Direction::North);

	// Player

	player = new Player(*this, *cell, "Player", "You look fine.");
	Item* const player_head = new Item(*this, *player, "Player Head", "Your head.", false, false, true);
	Item* const player_right_eye = new Item(*this, *player_head, "Player Right Eye", "Your right eye.", false, false, true);
	Item* const player_left_eye = new Item(*this, *player_head, "Player Left Eye", "Your left eye.", false, false, true);
	Item* const player_right_arm = new Item(*this, *player, "Player Right Arm", "Your right arm.", false, false, true);
	Item* const player_right_hand = new Item(*this, *player_right_arm, "Player Right Hand", "Your right hand.", true, false, true);
	Item* const player_left_arm = new Item(*this, *player, "Player Left Arm", "Your left arm.", false, false, true);
	Item* const player_left_hand = new Item(*this, *player_left_arm, "Player Left Hand", "Your left hand.", true, false, true);
	Item* const player_right_leg = new Item(*this, *player, "Player Right Leg", "Your right leg.", false, false, true);
	Item* const player_right_foot = new Item(*this, *player_right_leg, "Player Right Foot", "Your right foot.", false, false, true);
	Item* const player_left_leg = new Item(*this, *player, "Player Left Leg", "Your left leg.", false, false, true);
	Item* const player_left_foot = new Item(*this, *player_left_leg, "Player Left Foot", "Your left foot.", false, false, true);
}

World::~World()
{
	for (Entity* const entity : entities)
	{
		delete entity;
	}

	entities.clear();
}

void World::Tick(const std::vector<std::string>& tokens)
{
	const bool action_executed = ParseCommand(tokens);
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
			std::cout << "  take <object> - Picks up an item.\n";
			std::cout << "  drop <object> - Drops an item.\n";
			std::cout << "  put <object> in <object> - Puts an item inside an object.\n";
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
			const std::string name = JoinTokens(tokens, 1, tokens.size());

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
			const Direction direction = GetDirectionFromName(tokens[1]);
			if (direction != Direction::Unknown)
			{
				return player->Go(direction);
			}
		}
		else if (tokens[0] == "take")
		{
			const std::string name = JoinTokens(tokens, 1, tokens.size());

			if (player->Take(name))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (tokens[0] == "drop")
		{
			const std::string name = JoinTokens(tokens, 1, tokens.size());

			if (player->Drop(name))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (tokens[0] == "put")
		{
			int in_location = -1;
			for (int i = 1; i < tokens.size(); i++)
			{
				if (tokens[i] == "in")
				{
					in_location = i;
				}
			}
			if (in_location == -1)
			{
				std::cout << "You have to specify where to put the given item.\n\n";
				return false;
			}

			const std::string name = JoinTokens(tokens, 1, in_location);
			const std::string container_name = JoinTokens(tokens, in_location + 1, tokens.size());

			if (player->Put(name, container_name))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	std::cout << "I didn't understand what you wanted to do. Write 'help' to view the possible commands.\n\n";
	return false;
}
