#include <iostream>

#include "../utils/memory.h"
#include "../utils/offsets.h"

BOOL Memory::toggleBulletCheat(void) noexcept
{
	toggle.bBullet = !toggle.bBullet;
	std::cout << "Bullet Cheat " << (toggle.bBullet == TRUE ? "On" : "Off") << std::endl;
	return toggle.bBullet;
}

int Memory::executeBulletCheat() noexcept
{
	std::uintptr_t value = 0;

	value = Read<std::uintptr_t>(localPlayer + oCurrentWeaponClass);
	value = Read<std::uintptr_t>(value + oCurrentWeaponAmmoClass);
	Write<int>(value, 1000);
	return (0);
}