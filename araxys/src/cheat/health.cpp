#include <iostream>

#include "../utils/memory.h"
#include "../utils/offsets.h"

BOOL Memory::toggleHealthCheat(void) noexcept
{
	toggle.bHealth = !toggle.bHealth;
	std::cout << "Health Cheat " << (toggle.bHealth == TRUE ? "On" : "Off") << std::endl;
	return toggle.bHealth;
}

int Memory::executeHealthCheat() noexcept
{
	Write<int>(localPlayer + oHealth, 1000);
	return (0);
}