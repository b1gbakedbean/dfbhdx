#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdint>

namespace utils::memory
{
	template<typename T>
	void set(uintptr_t address, T value)
	{
		DWORD protect_value{};
		auto target = reinterpret_cast<uint8_t*>(address);
		auto size = sizeof(T);

		VirtualProtect(target, size, PAGE_EXECUTE_READWRITE, &protect_value);
		memset(target, value, size);
		VirtualProtect(target, size, protect_value, &protect_value);
		FlushInstructionCache(GetCurrentProcess(), target, size);
	}

	void jump(uintptr_t address, void* func);
	void set_string(uintptr_t address, const char* str);
	void nop(uintptr_t address, size_t length);
}