#include <iostream>

#include "../utils/memory.h"
#include "../utils/offsets.h"

BOOL Memory::toggleArmorCheat(void) noexcept
{
	toggle.bArmor = !toggle.bArmor;
	std::cout << "Armor Cheat " << (toggle.bArmor == TRUE ? "On" : "Off") << std::endl;
	return (toggle.bArmor);
}

int Memory::executeArmorCheat() noexcept
{
	Write<int>(localPlayer + oArmor, 1000);
	return (0);
}