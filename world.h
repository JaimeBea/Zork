#ifndef JAIMEBEA_ZORK_WORLD_H
#define JAIMEBEA_ZORK_WORLD_H

#include "common.h"

class World {
public:
	void Tick(const std::vector<const std::string>& tokens);
};

#endif // !JAIMEBEA_ZORK_WORLD_H
