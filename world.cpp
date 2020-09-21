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
	Item* const player_bed = new Item(*this, *cell, ItemType::Furniture, "Bed", "Your bed. It's a simple wooden bed with very little padding.", 100, 0, true, nullptr);
	Item* const envelope = new Item(*this, *player_bed, ItemType::Pickable, "Envelope", "A letter envelope.", 100, 10, true, nullptr);
	Item* const letter = new Item(*this, *envelope, ItemType::Pickable, "Letter", "\"I'll be waiting outside for you. Hurry up and win the fight!\"\n - Amor", 100, 10, false, nullptr);

	Room* const corridor = new Room(*this, "Jail Corridor", "The corridor extends to the east and west. There are cells to the north and south.");

	Room* const other_cell = new Room(*this, "Empty Cell", "The cell is very similar to the other one. The bed is broken and a plank with nails rests on the ground.");
	Item* const broken_bed = new Item(*this, *other_cell, ItemType::Furniture, "Broken bed", "The remains of a wooden bed. Looks like a heavy fight happened.", 100, 0, true, nullptr);
	Item* const board = new Item(*this, *broken_bed, ItemType::Pickable, "Board", "This board broke off from the broken bed.", 100, 10, false, nullptr);

	Room* const arena_lounge = new Room(*this, "Arena Lounge", "You find yourself at the arena lounge. You can see the light coming from the arena.");
	Item* const banana_peel = new Item(*this, *arena_lounge, ItemType::Pickable, "Banana Peel", "A banana peel.", 100, 10, false, nullptr);

	Room* const office = new Room(*this, "Office", "You are in your slavemaster Porcius' office. Porcius is distracted looking at some documents away from the door.");
	NPC* const porcius = new NPC(*this, *office, "Porcius", "Your slavemaster is extremely fat and ugly. His face resembles a pig.", 100);
	Item* const porcius_head = new Item(*this, *porcius, ItemType::BodyPart, "Porcius Head", "Porcius' head.", 100, 10, false, nullptr);
	Item* const porcius_right_eye = new Item(*this, *porcius_head, ItemType::BodyPart, "Porcius Right Eye", "Porcius' right eye.", 100, 10, false, nullptr);
	Item* const porcius_left_eye = new Item(*this, *porcius_head, ItemType::BodyPart, "Porcius Left Eye", "Porcius' left eye.", 100, 10, false, nullptr);
	Item* const porcius_right_arm = new Item(*this, *porcius, ItemType::BodyPart, "Porcius Right Arm", "Porcius' right arm.", 100, 10, false, nullptr);
	Item* const porcius_right_hand = new Item(*this, *porcius_right_arm, ItemType::BodyPart, "Porcius Right Hand", "Porcius' right hand.", 100, 10, true, nullptr);
	Item* const porcius_left_arm = new Item(*this, *porcius, ItemType::BodyPart, "Porcius Left Arm", "Porcius' left arm.", 100, 10, false, nullptr);
	Item* const porcius_left_hand = new Item(*this, *porcius_left_arm, ItemType::BodyPart, "Porcius Left Hand", "Porcius' left hand.", 100, 10, true, nullptr);
	Item* const porcius_right_leg = new Item(*this, *porcius, ItemType::BodyPart, "Porcius Right Leg", "Porcius' right leg.", 100, 10, false, nullptr);
	Item* const porcius_right_foot = new Item(*this, *porcius_right_leg, ItemType::BodyPart, "Porcius Right Foot", "Porcius' right foot.", 100, 10, false, nullptr);
	Item* const porcius_left_leg = new Item(*this, *porcius, ItemType::BodyPart, "Porcius Left Leg", "Porcius' left leg.", 100, 10, false, nullptr);
	Item* const porcius_left_foot = new Item(*this, *porcius_left_leg, ItemType::BodyPart, "Porcius Left Foot", "Porcius' left foot.", 100, 10, false, nullptr);
	Item* const dagger = new Item(*this, *porcius_right_arm, ItemType::Pickable, "Dagger", "Porcius' dagger. It's decorated with gems of multiple colors.", 100, 10, false, nullptr);
	Item* const desk_key = new Item(*this, *porcius_right_leg, ItemType::Pickable, "Desk Key", "It opens the desk in Porcius' office.", 100, 10, false, nullptr);
	Item* const desk = new Item(*this, *office, ItemType::Furniture, "Desk", "A wooden desk. There are multiple drawers.", 100, 0, true, desk_key);
	Item* const armory_key = new Item(*this, *desk, ItemType::Pickable, "Armory Key", "The key that opens the armory door.", 100, 10, false, nullptr);

	Room* const armory = new Room(*this, "Armory", "The armory is enormous. There are a lot of weapons to pick from.");
	Item* const sword = new Item(*this, *armory, ItemType::Pickable, "Sword", "Metal sword.", 100, 10, false, nullptr);
	Item* const mace = new Item(*this, *armory, ItemType::Pickable, "Mace", "Metal mace.", 100, 10, false, nullptr);
	Item* const spear = new Item(*this, *armory, ItemType::Pickable, "Spear", "Metal spear.", 100, 10, false, nullptr);
	Item* const shield = new Item(*this, *armory, ItemType::Pickable, "Shield", "Metal shield.", 100, 10, false, nullptr);

	Room* const arena = new Room(*this, "Arena", "The arena is filled with sand and blood stains. The public cheers for Kroz, who is smirking at you.");
	kroz = new NPC(*this, *arena, "Kroz", "He's about two heads taller than you. You can feel a great sense of danger.", 100);
	Item* const kroz_head = new Item(*this, *kroz, ItemType::BodyPart, "Kroz Head", "Kroz's head.", 100, 10, false, nullptr);
	Item* const kroz_right_eye = new Item(*this, *kroz_head, ItemType::BodyPart, "Kroz Right Eye", "Kroz's right eye.", 100, 10, false, nullptr);
	Item* const kroz_left_eye = new Item(*this, *kroz_head, ItemType::BodyPart, "Kroz Left Eye", "Kroz's left eye.", 100, 10, false, nullptr);
	Item* const kroz_right_arm = new Item(*this, *kroz, ItemType::BodyPart, "Kroz Right Arm", "Kroz's right arm.", 100, 10, false, nullptr);
	Item* const kroz_right_hand = new Item(*this, *kroz_right_arm, ItemType::BodyPart, "Kroz Right Hand", "Kroz's right hand.", 100, 10, true, nullptr);
	Item* const kroz_left_arm = new Item(*this, *kroz, ItemType::BodyPart, "Kroz Left Arm", "Kroz's left arm.", 100, 10, false, nullptr);
	Item* const kroz_left_hand = new Item(*this, *kroz_left_arm, ItemType::BodyPart, "Kroz Left Hand", "Kroz's left hand.", 100, 10, true, nullptr);
	Item* const kroz_right_leg = new Item(*this, *kroz, ItemType::BodyPart, "Kroz Right Leg", "Kroz's right leg.", 100, 10, false, nullptr);
	Item* const kroz_right_foot = new Item(*this, *kroz_right_leg, ItemType::BodyPart, "Kroz Right Foot", "Kroz's right foot.", 100, 10, false, nullptr);
	Item* const kroz_left_leg = new Item(*this, *kroz, ItemType::BodyPart, "Kroz Left Leg", "Kroz's left leg.", 100, 10, false, nullptr);
	Item* const kroz_left_foot = new Item(*this, *kroz_left_leg, ItemType::BodyPart, "Kroz Left Foot", "Kroz's left foot.", 100, 10, false, nullptr);
	Item* const axe = new Item(*this, *kroz_right_hand, ItemType::Pickable, "Axe", "Kroz's Axe. It's taller than you.", 100, 10, false, nullptr);
	Item* const morning_star = new Item(*this, *kroz_left_hand, ItemType::Pickable, "Morning Star", "Kroz's Morning Star. A huge metal mace with spikes.", 100, 10, false, nullptr);

	// Exits

	Exit* const cell_exit = new Exit(*this, "Player Cell Door", "Door made of vertical metal bars.", 100, *cell, *corridor, Direction::North, nullptr);
	Exit* const other_cell_exit = new Exit(*this, "Empty Cell Door", "Door made of vertical metal bars.", 100, *other_cell, *corridor, Direction::South, nullptr);
	Exit* const arena_lounge_corridor_exit = new Exit(*this, "Lounge Door", "Simple wooden door.", 100, *arena_lounge, *corridor, Direction::East, nullptr);
	Exit* const office_exit = new Exit(*this, "Office Door", "Simple wooden door.", 100, *office, *corridor, Direction::West, nullptr);
	Exit* const armory_exit = new Exit(*this, "Armory Door", "Full metal door with a keylock.", 100, *armory, *arena_lounge, Direction::North, armory_key);
	Exit* const arena_lounge_arena_exit = new Exit(*this, "Arena Entrance", "Very large wooden door.", 100, *arena_lounge, *arena, Direction::North, nullptr);

	// Player

	player = new Player(*this, *cell, "Player", "You look fine.", 100);
	Item* const player_head = new Item(*this, *player, ItemType::BodyPart, "Player Head", "Your head.", 100, 10, false, nullptr);
	Item* const player_right_eye = new Item(*this, *player_head, ItemType::BodyPart, "Player Right Eye", "Your right eye.", 100, 10, false, nullptr);
	Item* const player_left_eye = new Item(*this, *player_head, ItemType::BodyPart, "Player Left Eye", "Your left eye.", 100, 10, false, nullptr);
	Item* const player_right_arm = new Item(*this, *player, ItemType::BodyPart, "Player Right Arm", "Your right arm.", 100, 10, false, nullptr);
	Item* const player_right_hand = new Item(*this, *player_right_arm, ItemType::BodyPart, "Player Right Hand", "Your right hand.", 100, 10, true, nullptr);
	Item* const player_left_arm = new Item(*this, *player, ItemType::BodyPart, "Player Left Arm", "Your left arm.", 100, 10, false, nullptr);
	Item* const player_left_hand = new Item(*this, *player_left_arm, ItemType::BodyPart, "Player Left Hand", "Your left hand.", 100, 10, true, nullptr);
	Item* const player_right_leg = new Item(*this, *player, ItemType::BodyPart, "Player Right Leg", "Your right leg.", 100, 10, false, nullptr);
	Item* const player_right_foot = new Item(*this, *player_right_leg, ItemType::BodyPart, "Player Right Foot", "Your right foot.", 100, 10, false, nullptr);
	Item* const player_left_leg = new Item(*this, *player, ItemType::BodyPart, "Player Left Leg", "Your left leg.", 100, 10, false, nullptr);
	Item* const player_left_foot = new Item(*this, *player_left_leg, ItemType::BodyPart, "Player Left Foot", "Your left foot.", 100, 10, false, nullptr);
}

World::~World()
{
	for (Entity* const entity : entities)
	{
		delete entity;
	}
}

bool World::Tick(const std::vector<std::string>& tokens)
{
	const bool action_executed = ParseCommand(tokens);
	if (kroz->health == 0)
	{
		std::cout << "\n";
		std::cout << "Congratulations! You have achieved freedom!\n";
		std::cout << "\n";
		return true;
	}
	if (player->health == 0)
	{
		std::cout << "\n";
		std::cout << "You lose.\n";
		std::cout << "\n";
		return true;
	}

	return false;
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
			std::cout << "Objects:\n";
			std::cout << "  Everything inside the room or inside the objects of the room counts as an object.\n";
			std::cout << "  You have to be explicit when giving the name of an object or it won't be recognized.\n";
			std::cout << "Directions:\n";
			std::cout << "  The only accepted directions are north, south, east and west.\n";
			return false;
		}
		else if (tokens[0] == "examine")
		{
			const std::string name = JoinTokens(tokens, 1, tokens.size());

			if (player->OnExamine(name))
			{
				return false;
			}
			else
			{
				std::cout << "The thing you tried to examine doesn't exist.\n";
				return false;
			}
		}
		else if (tokens[0] == "go")
		{
			const Direction direction = GetDirectionFromName(tokens[1]);
			if (direction != Direction::Unknown)
			{
				return player->OnGo(direction);
			}
		}
		else if (tokens[0] == "take")
		{
			const std::string name = JoinTokens(tokens, 1, tokens.size());

			if (player->OnTake(name))
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

			if (player->OnDrop(name))
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
				std::cout << "You have to specify where to put the given item.\n";
				return false;
			}

			const std::string name = JoinTokens(tokens, 1, in_location);
			const std::string container_name = JoinTokens(tokens, in_location + 1, tokens.size());

			if (player->OnPut(name, container_name))
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
				std::cout << "You have to specify what you want to use.\n";
				return false;
			}

			const std::string target_name = JoinTokens(tokens, 1, with_location);
			const std::string source_name = JoinTokens(tokens, with_location + 1, tokens.size());

			if (player->OnHit(target_name, source_name))
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

			if (player->OnOpen(name))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	std::cout << "I didn't understand what you wanted to do. Write 'help' to view the possible commands.\n";
	return false;
}
