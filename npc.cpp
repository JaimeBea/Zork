#include "npc.h"

NPC::NPC(World& world, Room& location, const std::string& name, const std::string& description) : Creature(world, location, EntityType::NPC, name, description) {}
