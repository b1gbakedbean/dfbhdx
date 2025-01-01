#include "misc.hpp"
#include "utils/memory.hpp"

__declspec(naked) void antidebug_stub()
{
	__asm
	{
		mov eax, 0 // 0 = No debugger is present
		mov edi, eax
		neg edi
		sbb edi, edi
		push 0x428375
		retn
	}
}

namespace dfbhdx::components
{
	void misc::load()
	{
		utils::memory::set_string(0x626DA8, "DF:BHDx");

		utils::memory::nop(0x4623CB, 1);
		utils::memory::nop(0x4623E0, 6);

		utils::memory::nop(0x4628CC, 1);
		utils::memory::nop(0x4628E1, 6);

		utils::memory::nop(0x4B48E9, 8);

		utils::memory::nop(0x4D6E63, 1);
		utils::memory::nop(0x4D6E70, 6);

		utils::memory::nop(0x4DC266, 1);
		utils::memory::nop(0x4DC273, 6);

#ifdef _DEBUG
		utils::memory::jump(0x42836D, antidebug_stub);
#endif
	}

	void misc::unload()
	{

	}
}