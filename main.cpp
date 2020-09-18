#include "common.h"
#include "world.h"

int main()
{
	// Welcome player

	std::cout << "Welcome to Kroz the Gladiator!\n\n";

	std::cout << "You wake up inside your cell, a man knocking on your door.\n";
	std::cout << "- HEY! YOUR COMBAT IS STARTING SOON! WAKE UP!\n";
	std::cout << "The man walks away. You put your clothes on.\n\n";

	// Initialize world

	World world;

	// Game loop

	std::string player_input;
	std::vector<std::string> tokens;
	tokens.reserve(10);

	while (true)
	{
		std::getline(std::cin, player_input);
		Tokenize(player_input, tokens);

		std::cout << "\n"; // Double new line for easier reading

		if (player_input == "quit") break;

		world.Tick(tokens);
	}

	// Say goodbye to the player and exit

	std::cout << "Thanks for playing!\n\n";

	system("pause");
	return 0;
}
