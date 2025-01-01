#include "memory.hpp"

namespace utils::memory
{
	void jump(uintptr_t address, void* func)
	{
		auto target = reinterpret_cast<uint8_t*>(address);
		auto jmpValue = reinterpret_cast<uint32_t>(func) - (address + 5);
		DWORD oldProtectValue;

		VirtualProtect(target, 5, PAGE_EXECUTE_READWRITE, &oldProtectValue);
		*target = 0xE9;
		*reinterpret_cast<size_t*>(target + 1) = jmpValue;
		VirtualProtect(target, 5, oldProtectValue, &oldProtectValue);
		FlushInstructionCache(GetCurrentProcess(), target, 5);
	}

	void set_string(uintptr_t address, const char* str)
	{
		strncpy(reinterpret_cast<char*>(address), str, strlen(str) + 1);
	}

	void nop(uintptr_t address, size_t length)
	{
		auto target = reinterpret_cast<uint8_t*>(address);
		DWORD oldProtectValue;

		VirtualProtect(target, length, PAGE_EXECUTE_READWRITE, &oldProtectValue);
		memset(target, 0x90, length);
		VirtualProtect(target, length, oldProtectValue, &oldProtectValue);
		FlushInstructionCache(GetCurrentProcess(), target, length);
	}
}