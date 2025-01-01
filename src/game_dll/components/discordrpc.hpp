#pragma once
#include "component.hpp"

namespace dfbhdx::components
{
	class discordrpc : public component
	{
	public:
		virtual void load();
		virtual void unload();

	private:
		static void discordrpc_ready_callback(const DiscordUser* user);
		static void discordrpc_error_callback(int errorCode, const char* message);

		void initialize_discordrpc();
	};
}