add_library(game_dll SHARED "pch.cpp" "dllmain.cpp" "components/scripting.cpp" "components/misc.cpp" "components/rendering.cpp" "component_loader.cpp"  "directx/d3d8to9_base.cpp" "directx/d3d8to9_device.cpp" "directx/d3d8to9_index_buffer.cpp" "directx/d3d8to9_surface.cpp" "directx/d3d8to9_swap_chain.cpp" "directx/d3d8to9_texture.cpp" "directx/d3d8to9_vertex_buffer.cpp" "directx/d3d8to9_volume.cpp" "directx/d3d8types.cpp" "directx/interface_query.cpp" "game/game.cpp"  "components/imgui.cpp" "utils/memory.cpp" "components/discordrpc.cpp" "components/dispatcher.cpp" "components/network.cpp")
target_compile_features(game_dll PRIVATE cxx_std_17)
target_include_directories(game_dll PRIVATE .)
target_precompile_headers(game_dll PRIVATE "pch.hpp")

find_package(fmt CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_library(DISCORD_RPC_LIB discord-rpc)

target_link_libraries(game_dll PRIVATE fmt::fmt-header-only spdlog::spdlog_header_only imgui::imgui ${DISCORD_RPC_LIB})
set_target_properties(game_dll PROPERTIES OUTPUT_NAME dfbhdx)

if (COPY_PATH)
  add_custom_command(TARGET game_dll POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:game_dll> ${COPY_PATH}
    COMMAND_EXPAND_LISTS
  )
endif()