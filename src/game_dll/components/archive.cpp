#include "archive.hpp"
#include "utils/memory.hpp"
#include "game/game.hpp"

namespace dfbhdx::components
{
	static void load_custom_archives()
	{
		// Load the base dfbhdx PFF into the first slot, abort otherwise as it's required
		if (game::load_pff_archive(1, "dfbhdx/dfbhdx.pff"))
		{
			SPDLOG_INFO("Loaded PFF: dfbhdx.pff");
		}
		else
		{
			SPDLOG_INFO("Failed to load 'dfbhdx.pff', aborting application!");
			game::show_error_message("Failed to load: dfbhdx.pff");
		}

		// Load any other PFFs into the remaining PFF slots (these are optional)
		for (const auto& entry : std::filesystem::directory_iterator("dfbhdx/"))
		{
			// Skip directories and the base dfbhdx PFF as it was loaded first
			if (entry.is_directory() || entry.path().filename() == "dfbhdx.pff")
			{
				continue;
			}

			int slot = 2;

			if (entry.path().has_extension() && entry.path().extension() == ".pff" && slot <= 3)
			{
				if (game::load_pff_archive(slot, entry.path().string()))
				{
					slot++;
					SPDLOG_INFO("Loaded PFF: {}", entry.path().filename().string());
				}
			}
			else if (slot > 3) // No need to check any other files as we have no PFF slots remaining
			{
				SPDLOG_INFO("No remaining PFF slots available, no longer checking for any other PFFs.");
				break;
			}
		}
	}

	__declspec(naked) void load_custom_archives_stub()
	{
		__asm
		{
			call load_custom_archives
			mov eax, 0x00485520
			call eax
			push 0x0046A601
			retn
		}
	}

	void archive::load()
	{
		utils::memory::jump(0x0046A5FC, load_custom_archives_stub);
	}

	void archive::unload()
	{

	}
}