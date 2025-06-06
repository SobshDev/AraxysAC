#ifndef OFFSETS_H
#define OFFSETS_H

#include <iostream>

// LocalPlayer Offsets
constexpr std::uintptr_t oLocalPlayerPtr = 0x10F4F4;
constexpr int oHealth = 0xF8;
constexpr int oArmor = 0xFC;
constexpr int oShootDelay = 0x178;
constexpr int oCurrentWeaponClass = 0x374;
constexpr int oCurrentWeaponRecoilClass = 0x0C;
constexpr int oCurrentWeaponRecoilOffset = 0x120;
constexpr int oCurrentWeaponAmmoClass = 0x14;

// ASM Instruction Addresses
constexpr std::uintptr_t aRecoilInstruction = 0x462020;

// Entity Offsets
constexpr std::uintptr_t oEntityArrayPtr = 0x10F4F8;
constexpr int oXPos = 0x04;
constexpr int oYPos = 0x0C;
constexpr int oZPos = 0x08;

// Other Offsets
constexpr std::uintptr_t oPlayerCount = 0x10F500;

#endif //OFFSETS_H