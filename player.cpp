#include "player.h"
#include "room.h"
#include "exit.h"

Player::Player(World& world, std::string name, std::string description, Room& location) : Creature(world, EntityType::Player, name, description, location)
{
	location.Inspect();
}

// 'entity_name_tokens' is used as an auxiliary container. It will be cleared on every call.
bool CompareEntityNameWithTokens(const std::vector<std::string>& tokens, Entity& entity, std::vector<std::string>& entity_name_tokens)
{
	Tokenize(entity.name, entity_name_tokens);
	if (entity_name_tokens.size() != tokens.size() - 1) return false;
	for (int i = 0; i < entity_name_tokens.size(); ++i)
	{
		if (!CaseInsensitiveCompare(tokens[i + 1], entity_name_tokens[i])) return false;
	}

	return true;
}

bool RecursivelySearchEntities(const std::vector<std::string>& tokens, const std::list<Entity*>& entities, std::vector<std::string>& entity_name_tokens)
{
	for (Entity* entity : entities)
	{
		if (CompareEntityNameWithTokens(tokens, *entity, entity_name_tokens))
		{
			entity->Inspect();
			return true;
		}

		if (RecursivelySearchEntities(tokens, entity->contains, entity_name_tokens))
		{
			return true;
		}
	}

	return false;
}

bool Player::Examine(const std::vector<std::string>& tokens)
{
	if (tokens.size() == 1) // Tokens always include the word 'examine' at position 0
	{ 
		location->Inspect();
		return true;
	}
	else
	{
		std::vector<std::string> entity_name_tokens;

		if (RecursivelySearchEntities(tokens, location->contains, entity_name_tokens))
		{
			return true;
		}
	}

	return false;
}

bool Player::Go(Direction direction)
{
	Exit* exit = location->GetExit(direction);
	if (exit == nullptr)
	{
		std::cout << "You can't go " << GetDirectionName(direction) << "\n\n";
		return false;
	}

	Room* target;
	if (&exit->origin == location)
	{
		target = &exit->destination;
	}
	else
	{
		target = &exit->origin;
	}
	location->contains.remove(this);
	location = target;
	target->contains.push_back(this);

	target->Inspect();

	return true;
}
