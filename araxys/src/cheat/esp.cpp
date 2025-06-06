#include "esp.h"
#include "../utils/offsets.h"
#include "../utils/memory.h"

void ESP::refreshPlayerList(void) noexcept
{
	if (!m_memory)
		return;

	playerCount = m_memory->Read<int>(m_memory->getModuleBaseAddress() + oPlayerCount);
	if (playerCount < 0 || playerCount > 32)
		return;

	m_players.clear();
	std::uintptr_t currentEntity = 0;
	std::uintptr_t entityArray = m_memory->Read<std::uintptr_t>(m_memory->getModuleBaseAddress() + oEntityArrayPtr);
	float x, y, z;

	for (int i = 1; i < playerCount; i++) {
		currentEntity = m_memory->Read<std::uintptr_t>(entityArray + ((i) * 4));
		x = m_memory->Read<float>(currentEntity + oXPos);
		y = m_memory->Read<float>(currentEntity + oYPos);
		z = m_memory->Read<float>(currentEntity + oZPos);
		addPlayer(x, y, z);
	}

	std::uintptr_t localPlayer = m_memory->Read<std::uintptr_t>(m_memory->getModuleBaseAddress() + oLocalPlayerPtr);
	m_x = m_memory->Read<float>(localPlayer + oXPos);
	m_y = m_memory->Read<float>(localPlayer + oYPos);
	m_z = m_memory->Read<float>(localPlayer + oZPos);
}

BOOL Memory::actionESPRefresh() noexcept
{
	esp.refreshPlayerList();
	return (0);
}


BOOL Memory::executeESPPrint(void) noexcept
{
	esp.printPlayerPositions();
	return (0);
}
