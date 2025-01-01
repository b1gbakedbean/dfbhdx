#include "rendering.hpp"
#include "dispatcher.hpp"
#include "imgui.hpp"
#include "game/game.hpp"

bool debugEntities = false;
bool debugOrganics = false;
bool debugVehicles = false;
bool debugBuildings = false;
bool debugMarkers = false;
int debugEntityDistance = 50;

namespace dfbhdx::components
{
	void rendering::load()
	{
		dispatcher::add_callback(DispatcherCallbackType_Render, [](int ticks)
			{
				if (debugEntities)
				{
					if (debugOrganics)
					{
						for (auto entityIndex = 0u; entityIndex < 256; entityIndex++)
						{
							auto entity = game::get_entity(game::EntityType_Organic, entityIndex);

							if (!entity || game::get_distance_meters(game::get_local_player(), entity) > debugEntityDistance)
							{
								continue;
							}

							game::draw_text(entity, fmt::format("Index: {}\nSSN: {}", entityIndex, entity->ssn), game::rgb_color(0, 255, 0));
						}
					}

					if (debugVehicles)
					{
						for (auto entityIndex = 0u; entityIndex < 1200; entityIndex++)
						{
							auto entity = game::get_entity(game::EntityType_Vehicle, entityIndex);

							if (!entity || game::get_distance_meters(game::get_local_player(), entity) > debugEntityDistance)
							{
								continue;
							}

							game::draw_text(entity, fmt::format("Index: {}\nSSN: {}", entityIndex, entity->ssn), game::rgb_color(0, 255, 0));
						}
					}

					if (debugBuildings)
					{
						for (auto entityIndex = 0u; entityIndex < 1200; entityIndex++)
						{
							auto entity = game::get_entity(game::EntityType_Building, entityIndex);

							if (!entity || game::get_distance_meters(game::get_local_player(), entity) > debugEntityDistance)
							{
								continue;
							}

							game::draw_text(entity, fmt::format("Index: {}\nSSN: {}", entityIndex, entity->ssn), game::rgb_color(0, 255, 0));
						}
					}

					if (debugMarkers)
					{
						for (auto entityIndex = 0u; entityIndex < 768; entityIndex++)
						{
							auto entity = game::get_entity(game::EntityType_Marker, entityIndex);

							if (!entity || game::get_distance_meters(game::get_local_player(), entity) > debugEntityDistance)
							{
								continue;
							}

							game::draw_text(entity, fmt::format("Index: {}\nSSN: {}", entityIndex, entity->ssn), game::rgb_color(0, 255, 0));
						}
					}
				}

				// Everything below this line is related to the Dear ImGui menu
				if (!imgui::is_initialized || !imgui::is_menu_open)
				{
					return;
				}

				ImGui_ImplDX9_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();

				if (ImGui::Begin("Debug", &imgui::is_menu_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Checkbox("Debug entities", &debugEntities);
					ImGui::BeginDisabled(!debugEntities);
					ImGui::Checkbox("Players/NPCs", &debugOrganics);
					ImGui::Checkbox("Vehicles", &debugVehicles);
					ImGui::Checkbox("Buildings", &debugBuildings);
					ImGui::Checkbox("Markers", &debugMarkers);
					ImGui::InputInt("Distance (meters)", &debugEntityDistance);
					ImGui::EndDisabled();
					ImGui::End();
				}

				ImGui::EndFrame();
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			});
	}

	void rendering::unload()
	{

	}
}