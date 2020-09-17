#include "world.h"
#include "room.h"
#include "exit.h"

World::World()
{
	// Rooms

	Room* cell = new Room("Cell", "You find yourself inside a very small cell. There is a bed tucked in the corner and a door to the north.");
	entities.push_back(cell);
	Room* corridor = new Room("Jail Corridor", "The corridor extends to the east and west. There are cells to the north and south.");
	entities.push_back(corridor);
	Room* other_cell = new Room("Cell", "The cell is very similar to the other one. The bed is broken and a plank with nails rests on the ground. The exit is to the south.");
	entities.push_back(other_cell);
	Room* arena_lounge = new Room("Arena Lounge", "You find yourself at the arena lounge.");
	entities.push_back(arena_lounge);
	Room* office = new Room("Office", "You are in your slavemaster Porcius's office. Porcius is distracted looking at some documents away from the door.");
	entities.push_back(office);
	Room* arena = new Room("Arena", "The arena is filled with sand and blood stains. The public cheers for Kroz, who is smirking at you.");
	entities.push_back(arena);

	// Exits

	Exit* cell_exit = new Exit("Jail Door", "Metal door made of vertical bars.", *cell, *corridor, Direction::North);
	entities.push_back(cell_exit);
	Exit* other_cell_exit = new Exit("Jail Door", "Metal door made of vertical bars.", *other_cell, *corridor, Direction::South);
	entities.push_back(other_cell_exit);
	Exit* arena_lounge_corridor_exit = new Exit("Lounge Door", "This door takes you to the lounge.", *arena_lounge, *corridor, Direction::East);
	entities.push_back(arena_lounge_corridor_exit);
	Exit* office_exit = new Exit("Latrines Door", "This door takes you to the latrines.", *office, *corridor, Direction::West);
	entities.push_back(office_exit);
	Exit* arena_lounge_arena_exit = new Exit("Arena Entrance", "You can see light on the other side.", *arena_lounge, *arena, Direction::North);
	entities.push_back(arena_lounge_arena_exit);
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
	
}
