#include "utils/memory.hpp"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/msvc_sink.h"

#include "components/component.hpp"
#include "components/dispatcher.hpp"
//#include "components/scripting.hpp"
#include "components/network.hpp"
#include "components/imgui.hpp"
#include "components/rendering.hpp"
#include "components/discordrpc.hpp"
#include "components/misc.hpp"

#include "component_loader.hpp"

namespace dfbhdx
{
    void setup_logging()
    {
        std::vector<spdlog::sink_ptr> sinks
        {
            std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/dfbhdx.txt", 1048576 * 5, 25, true),
#ifdef _DEBUG
            std::make_shared<spdlog::sinks::msvc_sink_mt>()
#endif
        };

        auto logger = std::make_shared<spdlog::logger>("dfbhdx", sinks.begin(), sinks.end());

#ifdef _DEBUG
        logger->set_level(spdlog::level::trace);
#else
        logger->set_level(spdlog::level::info);
#endif
        spdlog::register_logger(logger);
        spdlog::set_default_logger(logger);
    }

    void initialize()
    {
        setup_logging();
        component_loader::add_component<dfbhdx::components::dispatcher>();
        //component_loader::add_component<dfbhdx::components::scripting>();
        component_loader::add_component<dfbhdx::components::network>();
        component_loader::add_component<dfbhdx::components::imgui>();
        component_loader::add_component<dfbhdx::components::rendering>();
        component_loader::add_component<dfbhdx::components::discordrpc>();
        component_loader::add_component<dfbhdx::components::misc>();
        component_loader::load_components();
    }

    void uninitialize()
    {
        component_loader::unload_components();
    }
}

__declspec(naked) void entry_point_start_hook()
{
    __asm
    {
        call dfbhdx::initialize
        push ebp
        mov ebp, esp
        push 0xFFFFFFFF
        push 0x569E65
        retn
    }
}

__declspec(naked) void entry_point_end_hook()
{
    __asm
    {
        call dfbhdx::uninitialize
        mov ecx, 0x5C5CFC
        call ecx
        push 0x5C5074
        retn
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        utils::memory::jump(0x569E60, entry_point_start_hook);
        utils::memory::jump(0x5C506F, entry_point_end_hook);
    }

    return TRUE;
}