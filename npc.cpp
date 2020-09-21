#include "npc.h"
#include "world.h"
#include "player.h"
#include "item.h"

NPC::NPC
(
	World& world,
	Room& location,
	NPCType npc_type,
	const std::string& name,
	const std::string& description,
	int health,
	float damage_multiplier
)
	: Creature(world, location, EntityType::NPC, name, description, health, damage_multiplier),
	npc_type(npc_type)
{}

Item* RecursivelySearchPickable(const Entity& parent)
{
	for (Entity* const entity : parent.contains)
	{
		if (entity->entity_type != EntityType::Item)
		{
			// Not an item
			continue;
		}

		Item* const item = dynamic_cast<Item*>(entity);
		if (item->item_type == ItemType::Pickable)
		{
			// Found pickable
			return item;
		}

		Item* const found_pickable = RecursivelySearchPickable(*item);
		if (found_pickable != nullptr)
		{
			return found_pickable;
		}
	}

	return nullptr;
}

void NPC::Update()
{
	if (world->player->location != location)
	{
		// Only update if the player is in the room
		return;
	}

	if (health == 0)
	{
		// Dead bodies don't update
		return;
	}

	if (npc_type == NPCType::Kroz)
	{
		// Select a weapon, or a random body part if he has none
		Item* selected_source = RecursivelySearchPickable(*this);
		if (selected_source == nullptr)
		{
			std::vector<Item*> possible_body_parts;
			possible_body_parts.reserve(20);
			for (Entity* const entity : contains)
			{
				if (entity->entity_type != EntityType::Item)
				{
					// Not an item (this should never happen)
					continue;
				}

				Item* const item = dynamic_cast<Item*>(entity);
				if (item->item_type == ItemType::BodyPart)
				{
					possible_body_parts.push_back(item);
				}
			}
			if (!possible_body_parts.empty())
			{
				int rand_index = rand() % possible_body_parts.size();
				selected_source = possible_body_parts[rand_index];
			}
		}

		// Select a target at random
		Item* selected_target = nullptr;
		std::vector<Item*> possible_targets;
		possible_targets.reserve(30);
		for (Entity* const entity : world->player->contains)
		{
			if (entity->entity_type != EntityType::Item)
			{
				// Not an item (this should never happen)
				continue;
			}

			Item* const item = dynamic_cast<Item*>(entity);
			possible_targets.push_back(item);
		}
		if (!possible_targets.empty())
		{
			int rand_index = rand() % possible_targets.size();
			selected_target = possible_targets[rand_index];
		}

		// Attack
		std::cout << "Kroz hits '" << selected_target->name << "' with '" << selected_source->name << "'!\n";
		selected_target->Damage(selected_source->damage);
	}
	else if (npc_type == NPCType::Porcius)
	{
		// Try to use the dagger, or run in circles if there is no dagger
		Entity* const dagger = SearchEntity("Dagger");
		if (dagger == nullptr)
		{
			std::cout << "Porcius is shouting and running in circles!\n";
			return;
		}
		Item* const dagger_item = dynamic_cast<Item*>(dagger);

		// Select a target at random
		Item* selected_target = nullptr;
		std::vector<Item*> possible_targets;
		possible_targets.reserve(30);
		for (Entity* const entity : world->player->contains)
		{
			if (entity->entity_type != EntityType::Item)
			{
				// Not an item (this should never happen)
				continue;
			}

			Item* const item = dynamic_cast<Item*>(entity);
			possible_targets.push_back(item);
		}
		if (!possible_targets.empty())
		{
			int rand_index = rand() % possible_targets.size();
			selected_target = possible_targets[rand_index];
		}

		// Attack
		std::cout << "Porcius hits '" << selected_target->name << "' with his dagger!\n";
		selected_target->Damage(dagger_item->damage);
	}
}

void NPC::Damage(int damage)
{
	const int previous_health = health;

	Creature::Damage(damage);

	if (health == 0)
	{
		if (previous_health != 0)
		{
			std::cout << "'" << name << "' dies and falls to the ground face first!\n";
		}
		else
		{
			std::cout << "'" << name << "' is already dead...\n";
		}
	}
	else if (health < starting_health / 2 && previous_health >= starting_health / 2)
	{
		std::cout << "'" << name << "' is wounded!\n";
	}
	else if (health < starting_health / 4 && previous_health >= starting_health / 4)
	{
		std::cout << "'" << name << "' is in critical condition!\n";
	}
}
