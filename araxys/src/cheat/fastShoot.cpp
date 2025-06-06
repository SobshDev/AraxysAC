#include <iostream>

#include "../utils/memory.h"
#include "../utils/offsets.h"


BOOL Memory::toggleFastShootCheat(void) noexcept
{
	toggle.bFastShoot = !toggle.bFastShoot;
	std::cout << "Fast Shoot Cheat " << (toggle.bFastShoot == TRUE ? "On" : "Off") << std::endl;
	return toggle.bFastShoot;
}

int Memory::executeFastShootCheat() noexcept
{
	Write<int>(localPlayer + oShootDelay, 0);
	return (0);
}