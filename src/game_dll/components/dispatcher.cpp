#include "dispatcher.hpp"
#include "utils/memory.hpp"

namespace dfbhdx::components
{
	static void dispatcher_run_callbacks(DispatcherCallbackType type)
	{
		static int ticks = 0;
		auto callbacks = dispatcher::get_callbacks();

		for (const auto& callback : callbacks)
		{
			if (callback.type == type)
			{
				callback.function(ticks);
			}
		}

		ticks++;
	}

	static __declspec(naked) void dispatcher_logic_loop_hook()
	{
		__asm
		{
			pushad // Preserve all registers as `dispatcher_run_callbacks` seems to overwrite `eax`, causing issues.
			push DispatcherCallbackType_Logic
			call dispatcher_run_callbacks
			add esp, 0x4
			popad
			mov ecx, [0x00655D7C]
			mov ecx, [ecx]
			push 0x004B497B
			retn
		}
	}

	static __declspec(naked) void dispatcher_render_loop_hook()
	{
		__asm
		{
			pushad
			push DispatcherCallbackType_Render
			call dispatcher_run_callbacks
			add esp, 0x4
			popad
			/*mov eax, 0x4F9D20
			call eax
			push 0x4B75A6
			retn*/
			push ebp
			mov ebp, esp
			sub esp, 0x5CC
			mov eax, 0x9F3710
			push 0x51CC2E
			retn
		}
	}

	void dispatcher::load()
	{
		// Hook the logic loop
		utils::memory::jump(0x4B4975, dispatcher_logic_loop_hook);

		// Hook the render loop
		utils::memory::jump(/*0x4B75A1*/0x51CC20, dispatcher_render_loop_hook);
	}

	void dispatcher::unload()
	{

	}

	void dispatcher::add_callback(DispatcherCallbackType type, std::function<void(int)> callback)
	{
		_callbacks.push_back({ type, callback });
	}

	std::vector<DispatcherCallback> dispatcher::get_callbacks()
	{
		return _callbacks;
	}
}