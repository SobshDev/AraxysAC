#include "iostream"

#include "../utils/memory.h"
#include "../utils/offsets.h"

BOOL Memory::toggleNoRecoilCheat(void) noexcept
{
	toggle.bNoRecoil = !toggle.bNoRecoil;
	std::cout << "No Recoil " << (toggle.bNoRecoil == TRUE ? "On" : "Off") << std::endl;
	return (toggle.bNoRecoil);
}

/* Original Code, Setting the Recoil of the Current Weapon Class to 0,
*  Coult Not turn the no Recoil cheat off
* 
int Memory::executeNoRecoilCheat() noexcept
{
	std::uintptr_t value = 0;

	value = Read<std::uintptr_t>(localPlayer + oCurrentWeaponClass);
	value = Read<std::uintptr_t>(value + oCurrentWeaponRecoilClass);
	Write<int>(value + oCurrentWeaponRecoilOffset, 0);
	return (0);
}
*/

int Memory::executeNoRecoilCheat() noexcept
{
    if (toggle.bNoRecoil == FALSE) {
        if (Read<BYTE>(aRecoilInstruction) == 0x55)
            return (0);        
        Write<BYTE>(aRecoilInstruction, 0x55);       // push ebp
        Write<BYTE>(aRecoilInstruction + 1, 0x8B);   // mov ebp,
        Write<BYTE>(aRecoilInstruction + 2, 0xEC);   // esp
    } else {
        if (Read<BYTE>(aRecoilInstruction) == 0xC2)
            return (0);
        Write<BYTE>(aRecoilInstruction, 0xC2);       // ret
        Write<BYTE>(aRecoilInstruction + 1, 0x08);   // 8 (stack cleanup size, low byte)
        Write<BYTE>(aRecoilInstruction + 2, 0x00);   // 0 (stack cleanup size, high byte)
    }
    return (0);
}