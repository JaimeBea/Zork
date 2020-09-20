#include "world.h"
#include "room.h"
#include "exit.h"
#include "player.h"
#include "npc.h"
#include "pickable.h"
#include "furniture.h"
#include "body_part.h"

World::World()
{
	// Rooms

	Room* const cell = new Room(*this, "Player Cell", "You find yourself inside a very small cell. There is a bed tucked in the corner.");
	Furniture* const player_bed = new Furniture(*this, *cell, "Bed", "Your bed. It's a simple wooden bed with very little padding.", 100, true, nullptr);
	Pickable* const envelope = new Pickable(*this, *player_bed, "Envelope", "A letter envelope.", 100, 10, true, nullptr);
	Pickable* const letter = new Pickable(*this, *envelope, "Letter", "\"I'll be waiting outside for you. Hurry up and win the fight!\"\n - Amor", 100, 10, false, nullptr);

	Room* const corridor = new Room(*this, "Jail Corridor", "The corridor extends to the east and west. There are cells to the north and south.");

	Room* const other_cell = new Room(*this, "Empty Cell", "The cell is very similar to the other one. The bed is broken and a plank with nails rests on the ground.");
	Furniture* const broken_bed = new Furniture(*this, *other_cell, "Broken bed", "The remains of a wooden bed. Looks like a heavy fight happened.", 100, true, nullptr);
	Pickable* const board = new Pickable(*this, *broken_bed, "Board", "This board broke off from the broken bed.", 100, 10, false, nullptr);

	Room* const arena_lounge = new Room(*this, "Arena Lounge", "You find yourself at the arena lounge. You can see the light coming from the arena.");
	Pickable* const banana_peel = new Pickable(*this, *arena_lounge, "Banana Peel", "A banana peel.", 100, 10, false, nullptr);

	Room* const office = new Room(*this, "Office", "You are in your slavemaster Porcius' office. Porcius is distracted looking at some documents away from the door.");
	NPC* const porcius = new NPC(*this, *office, "Porcius", "Your slavemaster is extremely fat and ugly. His face resembles a pig.", 100);
	BodyPart* const porcius_head = new BodyPart(*this, *porcius, "Porcius Head", "Porcius' head.", 100, 10, true, false);
	BodyPart* const porcius_right_eye = new BodyPart(*this, *porcius_head, "Porcius Right Eye", "Porcius' right eye.", 100, 10, true, false);
	BodyPart* const porcius_left_eye = new BodyPart(*this, *porcius_head, "Porcius Left Eye", "Porcius' left eye.", 100, 10, true, false);
	BodyPart* const porcius_right_arm = new BodyPart(*this, *porcius, "Porcius Right Arm", "Porcius' right arm.", 100, 10, true, false);
	BodyPart* const porcius_right_hand = new BodyPart(*this, *porcius_right_arm, "Porcius Right Hand", "Porcius' right hand.", 100, 10, true, true);
	BodyPart* const porcius_left_arm = new BodyPart(*this, *porcius, "Porcius Left Arm", "Porcius' left arm.", 100, 10, true, false);
	BodyPart* const porcius_left_hand = new BodyPart(*this, *porcius_left_arm, "Porcius Left Hand", "Porcius' left hand.", 100, 10, true, true);
	BodyPart* const porcius_right_leg = new BodyPart(*this, *porcius, "Porcius Right Leg", "Porcius' right leg.", 100, 10, true, false);
	BodyPart* const porcius_right_foot = new BodyPart(*this, *porcius_right_leg, "Porcius Right Foot", "Porcius' right foot.", 100, 10, true, false);
	BodyPart* const porcius_left_leg = new BodyPart(*this, *porcius, "Porcius Left Leg", "Porcius' left leg.", 100, 10, true, false);
	BodyPart* const porcius_left_foot = new BodyPart(*this, *porcius_left_leg, "Porcius Left Foot", "Porcius' left foot.", 100, 10, true, false);
	Pickable* const dagger = new Pickable(*this, *porcius_right_arm, "Dagger", "Porcius' dagger. It's decorated with gems of multiple colors.", 100, 10, false, nullptr);
	Pickable* const desk_key = new Pickable(*this, *porcius_right_leg, "Desk Key", "It opens the desk in Porcius' office.", 100, 10, false, nullptr);
	Furniture* const desk = new Furniture(*this, *office, "Desk", "A wooden desk. There are multiple drawers.", 100, true, desk_key);
	Pickable* const armory_key = new Pickable(*this, *desk, "Armory Key", "The key that opens the armory door.", 100, 10, false, nullptr);

	Room* const armory = new Room(*this, "Armory", "The armory is enormous. There are a lot of weapons to pick from.");
	Pickable* const sword = new Pickable(*this, *armory, "Sword", "Metal sword.", 100, 10, false, nullptr);
	Pickable* const mace = new Pickable(*this, *armory, "Mace", "Metal mace.", 100, 10, false, nullptr);
	Pickable* const spear = new Pickable(*this, *armory, "Spear", "Metal spear.", 100, 10, false, nullptr);
	Pickable* const shield = new Pickable(*this, *armory, "Shield", "Metal shield.", 100, 10, false, nullptr);

	Room* const arena = new Room(*this, "Arena", "The arena is filled with sand and blood stains. The public cheers for Kroz, who is smirking at you.");
	NPC* const kroz = new NPC(*this, *arena, "Kroz", "He's about two heads taller than you. You can feel a great sense of danger.", 100);
	BodyPart* const kroz_head = new BodyPart(*this, *kroz, "Kroz Head", "Kroz's head.", 100, 10, true, false);
	BodyPart* const kroz_right_eye = new BodyPart(*this, *kroz_head, "Kroz Right Eye", "Kroz's right eye.", 100, 10, true, false);
	BodyPart* const kroz_left_eye = new BodyPart(*this, *kroz_head, "Kroz Left Eye", "Kroz's left eye.", 100, 10, true, false);
	BodyPart* const kroz_right_arm = new BodyPart(*this, *kroz, "Kroz Right Arm", "Kroz's right arm.", 100, 10, true, false);
	BodyPart* const kroz_right_hand = new BodyPart(*this, *kroz_right_arm, "Kroz Right Hand", "Kroz's right hand.", 100, 10, true, true);
	BodyPart* const kroz_left_arm = new BodyPart(*this, *kroz, "Kroz Left Arm", "Kroz's left arm.", 100, 10, true, false);
	BodyPart* const kroz_left_hand = new BodyPart(*this, *kroz_left_arm, "Kroz Left Hand", "Kroz's left hand.", 100, 10, true, true);
	BodyPart* const kroz_right_leg = new BodyPart(*this, *kroz, "Kroz Right Leg", "Kroz's right leg.", 100, 10, true, false);
	BodyPart* const kroz_right_foot = new BodyPart(*this, *kroz_right_leg, "Kroz Right Foot", "Kroz's right foot.", 100, 10, true, false);
	BodyPart* const kroz_left_leg = new BodyPart(*this, *kroz, "Kroz Left Leg", "Kroz's left leg.", 100, 10, true, false);
	BodyPart* const kroz_left_foot = new BodyPart(*this, *kroz_left_leg, "Kroz Left Foot", "Kroz's left foot.", 100, 10, true, false);
	Pickable* const axe = new Pickable(*this, *kroz_right_hand, "Axe", "Kroz's Axe. It's taller than you.", 100, 10, false, nullptr);
	Pickable* const morning_star = new Pickable(*this, *kroz_left_hand, "Morning Star", "Kroz's Morning Star. A huge metal mace with spikes.", 100, 10, false, nullptr);

	// Exits

	Exit* const cell_exit = new Exit(*this, "Player Cell Door", "Door made of vertical metal bars.", 100, *cell, *corridor, Direction::North, nullptr);
	Exit* const other_cell_exit = new Exit(*this, "Empty Cell Door", "Door made of vertical metal bars.", 100, *other_cell, *corridor, Direction::South, nullptr);
	Exit* const arena_lounge_corridor_exit = new Exit(*this, "Lounge Door", "Simple wooden door.", 100, *arena_lounge, *corridor, Direction::East, nullptr);
	Exit* const office_exit = new Exit(*this, "Office Door", "Simple wooden door.", 100, *office, *corridor, Direction::West, nullptr);
	Exit* const armory_exit = new Exit(*this, "Armory Door", "Full metal door with a keylock.", 100, *armory, *arena_lounge, Direction::North, armory_key);
	Exit* const arena_lounge_arena_exit = new Exit(*this, "Arena Entrance", "Very large wooden door.", 100, *arena_lounge, *arena, Direction::North, nullptr);

	// Player

	player = new Player(*this, *cell, "Player", "You look fine.", 100);
	BodyPart* const player_head = new BodyPart(*this, *player, "Player Head", "Your head.", 100, 10, true, false);
	BodyPart* const player_right_eye = new BodyPart(*this, *player_head, "Player Right Eye", "Your right eye.", 100, 10, true, false);
	BodyPart* const player_left_eye = new BodyPart(*this, *player_head, "Player Left Eye", "Your left eye.", 100, 10, true, false);
	BodyPart* const player_right_arm = new BodyPart(*this, *player, "Player Right Arm", "Your right arm.", 100, 10, true, false);
	BodyPart* const player_right_hand = new BodyPart(*this, *player_right_arm, "Player Right Hand", "Your right hand.", 100, 10, true, true);
	BodyPart* const player_left_arm = new BodyPart(*this, *player, "Player Left Arm", "Your left arm.", 100, 10, true, false);
	BodyPart* const player_left_hand = new BodyPart(*this, *player_left_arm, "Player Left Hand", "Your left hand.", 100, 10, true, true);
	BodyPart* const player_right_leg = new BodyPart(*this, *player, "Player Right Leg", "Your right leg.", 100, 10, true, false);
	BodyPart* const player_right_foot = new BodyPart(*this, *player_right_leg, "Player Right Foot", "Your right foot.", 100, 10, true, false);
	BodyPart* const player_left_leg = new BodyPart(*this, *player, "Player Left Leg", "Your left leg.", 100, 10, true, false);
	BodyPart* const player_left_foot = new BodyPart(*this, *player_left_leg, "Player Left Foot", "Your left foot.", 100, 10, true, false);
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
			std::cout << "  hit <object> with <object> - Hits something with the given object.\n";
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
		else if (tokens[0] == "hit")
		{
			int with_location = -1;
			for (int i = 1; i < tokens.size(); i++)
			{
				if (tokens[i] == "with")
				{
					with_location = i;
				}
			}
			if (with_location == -1)
			{
				std::cout << "You have to specify what you want to use.\n\n";
				return false;
			}

			const std::string target_name = JoinTokens(tokens, 1, with_location);
			const std::string source_name = JoinTokens(tokens, with_location + 1, tokens.size());

			if (player->Hit(target_name, source_name))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (tokens[0] == "open")
		{
			const std::string name = JoinTokens(tokens, 1, tokens.size());

			if (player->Open(name))
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
