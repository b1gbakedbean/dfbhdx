#include "game.hpp"
#include "directx/d3d8to9.hpp"

namespace game
{
	// The internal namespace holds the raw functions and variables from the game
	namespace internal
	{
		// Functions
		draw_box_t draw_box = draw_box_t(0x004B5930);
		draw_text_t draw_text = draw_text_t(0x0052DD90);
		get_font_width_text_t get_font_width_text = get_font_width_text_t(0x004F7080);
		get_font_width_t get_font_width = get_font_width_t(0x004F70B0);
		svr_punt_player_t svr_punt_player = svr_punt_player_t(0x004A8120);
		svr_endgame_t svr_endgame = svr_endgame_t(0x004A3540);
		set_world_coords_t set_world_coords = set_world_coords_t(0x004416A0);
		transform_world_t transform_world = transform_world_t(0x00560160);
		convert_world_to_screen_t convert_world_to_screen = convert_world_to_screen_t(0x00502D60);
		get_distance_t get_distance = get_distance_t(0x0055E6A0);
		set_loaded_pff_archive_t set_loaded_pff_archive = set_loaded_pff_archive_t(0x00564FC0);
		load_pff_archive_t load_pff_archive = load_pff_archive_t(0x0056C970);
		exit_application_t exit_application = exit_application_t(0x00569020);

		// Variables
		HWND* hwnd = reinterpret_cast<HWND*>(0x00F654FC);
		int* frames_per_second = reinterpret_cast<int*>(0x009F3724);
		void* game_res = reinterpret_cast<void*>(0x009F72C0);
		void* font = reinterpret_cast<void*>(0x0095B9BC);
		uint32_t* is_host = reinterpret_cast<uint32_t*>(0x009F2190);
		ServerStruct** server = reinterpret_cast<ServerStruct**>(0x009ED600);
		int* model_count = reinterpret_cast<int*>(0x00D06060);
		Entity** organics = reinterpret_cast<Entity**>(0x00715900);
		Entity** vehicles = reinterpret_cast<Entity**>(0x00715904);
		Entity** buildings = reinterpret_cast<Entity**>(0x00715908);
		Entity** markers = reinterpret_cast<Entity**>(0x0071590C);
		void* world_matrix = reinterpret_cast<void*>(0x007159EC);
		Entity** local_player = reinterpret_cast<Entity**>(0x0096C290);
	}

	// Everything below here is our custom functions that are mostly wrappers around the internal functions/variables

	int rgb_color(int r, int g, int b)
	{
		return (r << 16) + (g << 8) + b;
	}

	void draw_box(BoxBounds bounds, std::string title)
	{
		internal::draw_box(internal::game_res, bounds.x1, bounds.y1, bounds.x2, bounds.y2, title.c_str(), 0xFF);
	}

	void draw_text(int x, int y, std::string text, int color)
	{
		auto text_width = internal::get_font_width_text(text.c_str(), internal::font);

		internal::draw_text(internal::game_res, x + (text_width / 2), y, 0, text.c_str(), internal::font, color, 2);
	}

	void draw_text(Entity* entity, std::string text, int color)
	{
		auto width = internal::get_font_width(48, internal::font);
		Vector3 screenPos{};

		if (!world_to_screen(&screenPos, entity))
		{
			return;
		}

		screenPos.y -= width;

		internal::draw_text(internal::game_res, screenPos.x, screenPos.y, 0, text.c_str(), internal::font, color, 2);
	}

	int get_fps()
	{
		return *internal::frames_per_second;
	}

	HWND get_hwnd()
	{
		return *internal::hwnd;
	}

	IDirect3DDevice9* get_d3d_device()
	{
		auto d3d_device = *reinterpret_cast<Direct3DDevice8**>(0x00E9E564);
		auto proxy_device = d3d_device->GetProxyInterface();

		return proxy_device;
	}

	bool is_host()
	{
		return *internal::is_host;
	}

	ServerStruct* get_server()
	{
		return *internal::server;
	}

	int game::get_model_count()
	{
		return *internal::model_count;
	}

	void punt_player(int index)
	{
		if (!is_host())
		{
			return;
		}

		internal::svr_punt_player(index);
	}

	Entity* get_entity(EntityType type, int index)
	{
		assert(type <= 3 && "type cannot be greater than 3");
		assert(type >= 0 && "type cannot be less than 0");
		assert(index >= 0 && "index cannot be less than 0");

		Entity** base_ptr = nullptr;

		switch (type)
		{
		case EntityType_Organic:
			base_ptr = internal::organics;
			break;

		case EntityType_Vehicle:
			base_ptr = internal::vehicles;
			break;

		case EntityType_Building:
			base_ptr = internal::buildings;
			break;

		case EntityType_Marker:
			base_ptr = internal::markers;
			break;

		default:
			return nullptr;
		}

		auto entity = *base_ptr + index;

		if (entity->itemDefinitionIndex == 0)
		{
			return nullptr;
		}

		return entity;
	}

	bool world_to_screen(Vector3* screenPosition, Entity* entity)
	{
		internal::set_world_coords(screenPosition, entity);

		if (entity->itemDefinition->type == ItemType_Person)
		{
			screenPosition->z += 32768;
		}

		internal::transform_world(internal::world_matrix, screenPosition, screenPosition);

		if (internal::convert_world_to_screen(screenPosition))
		{
			return false;
		}

		return true;
	}

	int get_distance_meters(Entity* a, Entity* b)
	{
		auto xDiffAbs = abs(a->position.x - b->position.x);
		auto yDiffAbs = abs(a->position.y - b->position.y);
		auto zDiffAbs = abs(a->position.z - b->position.z);

		return internal::get_distance(xDiffAbs, yDiffAbs, zDiffAbs) / 65536;
	}

	Entity* get_local_player()
	{
		return *internal::local_player;
	}

	bool load_pff_archive(unsigned int slot, const std::string& fileName)
	{
		auto archive = internal::load_pff_archive(fileName.c_str());

		if (!archive)
		{
			return false;
		}

		internal::set_loaded_pff_archive(slot, archive);

		return true;
	}

	void show_error_message(const std::string& error_message, bool exit)
	{
		MessageBoxA(get_hwnd(), error_message.c_str(), "Program Error", MB_OK);

		if (exit)
		{
			internal::exit_application();
		}
	}
}