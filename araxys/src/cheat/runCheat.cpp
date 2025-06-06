#include <iostream>

#include "../utils/memory.h"
#include "../utils/offsets.h"


int Memory::runCheat(void) noexcept
{
	if (moduleBaseAddress == 0) {
		std::cout << "Assault Cube not found !";
		return (1);
	}
	if (localPlayer == 0) {
		localPlayer = Read<int>(moduleBaseAddress + oLocalPlayerPtr);
	} else {
		if (toggle.bArmor)
			executeArmorCheat();
		if (toggle.bBullet)
			executeBulletCheat();
		if (toggle.bFastShoot)
			executeFastShootCheat();
		if (toggle.bHealth)
			executeHealthCheat();
		executeNoRecoilCheat();
	}
	return 0;
}