#include "common.h"
#include "world.h"

int main() {
	std::cout << "Welcome to Kroz the Gladiator!\n\n";

	World world;

	std::string player_input;
	std::vector<const std::string> tokens;
	
	tokens.reserve(10);

	while (true) {
		std::cout << "What do you want?\n";

		std::getline(std::cin, player_input);
		Tokenize(player_input, tokens);

		world.Tick(tokens);

		if (player_input == "exit") break;
	}

	std::cout << "Thanks for playing!\n\n";
	system("pause");
	return 0;
}
