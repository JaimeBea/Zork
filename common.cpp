#include "common.h"

void Tokenize(const std::string& input, std::vector<const std::string>& output) {
	output.clear();

	size_t prev = 0;
	size_t next = 0;

	next = input.find_first_of(' ', prev);
	while (next != std::string::npos) {
		output.push_back(input.substr(prev, next - prev));

		prev = next + 1;
		next = input.find_first_of(' ', prev);
	}
}
