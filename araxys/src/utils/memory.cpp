#include "memory.h"
const std::uintptr_t Memory::GetModuleaddress(const std::string_view moduleName) noexcept
{
	::MODULEENTRY32 entry = {};
	entry.dwSize = sizeof(::MODULEENTRY32);

	const auto processSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

	std::uintptr_t moduleBaseAddress = 0;
	while (::Module32Next(processSnapshot, &entry)) {
		if (!moduleName.compare(entry.szModule)) {
			moduleBaseAddress = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
			break;
		}
	}
	if (processSnapshot)
		::CloseHandle(processSnapshot);
	return moduleBaseAddress;
}
