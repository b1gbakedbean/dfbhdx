/*
#include "scripting.hpp"
#include "utils/memory.hpp"

namespace dfbhdx::components
{
	void scripting::execute_init_callbacks()
	{
		for (auto& init_callback : _init_callbacks)
		{
			init_callback();
		}
	}

	__declspec(naked) void on_init_hook()
	{
		__asm
		{
			call scripting::execute_init_callbacks
			push ebp
			mov ebp, esp
			sub esp, 0x914
			push 0x4B9469
			retn
		}
	}

	void scripting::execute_on_frame_callbacks()
	{
		for (auto& on_frame_callback : _on_frame_callbacks)
		{
			on_frame_callback();
		}
	}

	__declspec(naked) void on_frame_hook()
	{
		__asm
		{
			call scripting::execute_on_frame_callbacks
			// Finish hook
		}
	}

	void scripting::load()
	{
		setup_state();

		utils::memory::jump(0x4B9460, on_init_hook);
		//utils::memory::jump(0x0, on_frame_hook);

		load_scripts();
		execute_scripts();
	}

	void scripting::unload()
	{

	}

	void scripting::load_scripts()
	{
		if (!std::filesystem::exists("scripts") || !std::filesystem::is_directory("scripts"))
		{
			return;
		}

		for (const auto& entry : std::filesystem::recursive_directory_iterator{ "scripts" })
		{
			if (!entry.is_regular_file())
			{
				continue;
			}

			auto& path = entry.path();

			if (path.has_extension() && path.extension() == ".lua")
			{
				SPDLOG_DEBUG("Found script: {}", path.string());
				_scripts.push_back(path.string());
			}
		}

		SPDLOG_INFO("Loaded {} script(s)", _scripts.size());
	}

	void scripting::clear_scripts()
	{
		_scripts.clear();
	}

	void scripting::reload_scripts()
	{
		clear_scripts();
		load_scripts();
	}

	void scripting::execute_scripts()
	{
		for (const auto& script : _scripts)
		{
			_lua.script_file(script);
		}
	}

	void scripting::setup_state()
	{
		_lua.set_function("test", [](int a, int b)
			{
				SPDLOG_DEBUG("{} {}", a, b);
			});
		_lua.set_function("registerInit", [&](sol::function f)
			{
				_init_callbacks.push_back(f);
			});
		_lua.set_function("registerOnFrame", [&](sol::function f)
			{
				_on_frame_callbacks.push_back(f);
			});
	}
}
*/