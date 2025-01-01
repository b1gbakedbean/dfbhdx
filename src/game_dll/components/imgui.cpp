#include "imgui.hpp"
#include "game/game.hpp"
#include "utils/memory.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace dfbhdx::components
{
	WNDPROC o_wndProc = nullptr;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (msg == WM_KEYUP && wParam == VK_DELETE)
		{
			imgui::is_menu_open = !imgui::is_menu_open;
		}

		if (imgui::is_menu_open)
		{
			return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		}

		return CallWindowProc(o_wndProc, hWnd, msg, wParam, lParam);
	}

	static bool hook_wndproc()
	{
		auto ptr = SetWindowLongPtr(game::get_hwnd(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc));

		if (ptr == 0)
		{
			SPDLOG_DEBUG("SetWindowLongPtr() failed: {}", GetLastError());
			return false;
		}

		o_wndProc = reinterpret_cast<WNDPROC>(ptr);

		return true;
	}

	static void initialize_imgui()
	{
		if (game::get_hwnd() == nullptr || game::get_d3d_device() == nullptr)
		{
			SPDLOG_DEBUG("get_hwnd() or get_d3d_device() returned null");
			return;
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		
		auto& io = ImGui::GetIO();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NoMouse;

		if (!hook_wndproc())
		{
			SPDLOG_DEBUG("Failed to hook WndProc");
			return;
		}

		ImGui_ImplWin32_Init(game::get_hwnd());
		ImGui_ImplDX9_Init(game::get_d3d_device());

		imgui::is_initialized = true;
	}

	static __declspec(naked) void initialize_imgui_stub()
	{
		__asm
		{
			call initialize_imgui
			push eax
			mov eax, 0x0056B940
			call eax
			pop eax
			push 0x0046A740
			retn
		}
	}

	void imgui::load()
	{
		utils::memory::jump(0x0046A73B, initialize_imgui_stub);
	}

	void imgui::unload()
	{
		if (!is_initialized)
		{
			return;
		}

		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
}