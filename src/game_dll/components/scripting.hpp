/*
#pragma once
#include "component.hpp"

namespace dfbhdx::components
{
	class scripting : public component
	{
	public:
		virtual void load();
		virtual void unload();
		static void execute_init_callbacks();
		static void execute_on_frame_callbacks();

	private:
		void load_scripts();
		void clear_scripts();
		void reload_scripts();
		void execute_scripts();
		void setup_state();

		inline static std::vector<sol::function> _init_callbacks;
		inline static std::vector<sol::function> _on_frame_callbacks;
		std::vector<std::string> _scripts;
		sol::state _lua;
	};
}
*/