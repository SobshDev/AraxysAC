#ifndef MEMORY_H
#define MEMORY_H

#include "../cheat/esp.h"

#include <cstdint>
#include <Windows.h>
#include <TlHelp32.h>
#include <string_view>

typedef struct toggle_s {
	BOOL bHealth;
	BOOL bArmor;
	BOOL bBullet;
	BOOL bFastShoot;
	BOOL bNoRecoil;
} toggle_t;

class Memory
{
	private:
		std::uintptr_t processId = 0;
		void *processHandle = nullptr;
		std::uintptr_t moduleBaseAddress = 0;
		std::uintptr_t localPlayer = 0;
		std::uintptr_t weaponAmmoAddress = 0;
		toggle_t toggle = {};
		ESP esp;
	
public:
	Memory(const std::string_view processName) noexcept
	{
		::PROCESSENTRY32 entry = { };
		entry.dwSize = sizeof(::PROCESSENTRY32);

		const auto processSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		while (::Process32Next(processSnapshot, &entry)) {
			if (!processName.compare(entry.szExeFile)) {
				processId = entry.th32ProcessID;
				processHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
				break;
			}
		}
		if (processSnapshot)
			::CloseHandle(processSnapshot);
		moduleBaseAddress = GetModuleaddress(processName);

		esp.setMemory(this);
	}

	~Memory()
	{
		if (processHandle)
			::CloseHandle(processHandle);
	}

	const std::uintptr_t GetModuleaddress(const std::string_view moduleName) noexcept;

	template <typename T>
	const T Read(const std::uintptr_t& address) noexcept
	{
		T value = {};

		::ReadProcessMemory(processHandle, reinterpret_cast<const void*>(address), &value, sizeof(T), NULL);
		return (value);
	}

	template <typename T>
	const void Write(const std::uintptr_t& address, const T& value) noexcept
	{
		::WriteProcessMemory(processHandle, reinterpret_cast<void*>(address), &value, sizeof(T), NULL);
	}

	public:
		BOOL toggleHealthCheat(void) noexcept;
		BOOL toggleArmorCheat(void) noexcept;
		BOOL toggleBulletCheat(void) noexcept;
		BOOL toggleFastShootCheat(void) noexcept;
		BOOL toggleNoRecoilCheat(void) noexcept;
		BOOL actionESPRefresh(void) noexcept;
		BOOL executeESPPrint(void) noexcept;

	public:
		int runCheat(void) noexcept;

	private:
		int executeHealthCheat() noexcept;
		int executeArmorCheat() noexcept;
		int executeBulletCheat() noexcept;
		int executeFastShootCheat() noexcept;
		int executeNoRecoilCheat() noexcept;

	public:
		std::uintptr_t getModuleBaseAddress(void) noexcept { return (moduleBaseAddress); };

};

#endif // MEMORY_H
