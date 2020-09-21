#include "common.h"
#include "world.h"

void Play(std::string& player_input, std::vector<std::string> tokens)
{
	// Initialize world
	std::cout << "\n";
	std::cout << "You wake up inside your cell, a man knocking on your door.\n";
	std::cout << "- HEY! YOUR COMBAT IS STARTING SOON! WAKE UP!\n";
	std::cout << "The man walks away. You put your clothes on.\n";
	std::cout << "\n";

	World world;

	// Game loop
	while (true)
	{
		std::cout << "\n";
		std::cout << "> ";
		std::getline(std::cin, player_input);
		Tokenize(player_input, tokens);
		std::cout << "\n";

		if (player_input == "quit")
		{
			break;
		}

		const bool finished = world.Tick(tokens);
		if (finished)
		{
			break;
		}
	}
}

int main()
{
	std::cout << "Welcome to Kroz the Gladiator!\n";

	std::string player_input;
	std::vector<std::string> tokens;
	tokens.reserve(10);

	while (true)
	{
		Play(player_input, tokens);

		std::cout << "Do you want to try again?\n";
		std::cout << "\n";
		std::cout << "> ";
		std::getline(std::cin, player_input);
		Tokenize(player_input, tokens);

		if (player_input != "yes")
		{
			break;
		}
	}

	std::cout << "\n";
	std::cout << "Thanks for playing!\n";
	std::cout << "\n";
	system("pause");
	return 0;
}
