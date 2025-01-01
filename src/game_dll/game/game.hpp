#pragma once
#include "structs.hpp"

namespace game
{
	// The internal namespace holds the raw functions and variables from the game
	namespace internal
	{
		// Functions
		typedef void (*draw_box_t)(void* game_resolution, int x1, int y1, int x2, int y2, const char* title, int);
		extern draw_box_t draw_box;

		typedef void (*draw_text_t)(void* game_resolution, int x, int y, int, const char* text, void* font, int, int);
		extern draw_text_t draw_text;

		typedef unsigned int (*get_font_width_text_t)(const char* text, void* font);
		extern get_font_width_text_t get_font_width_text;

		typedef unsigned int (*get_font_width_t)(int, void* font);
		extern get_font_width_t get_font_width;

		typedef void (*svr_punt_player_t)(int index);
		extern svr_punt_player_t svr_punt_player;

		typedef void (*svr_endgame_t)(int type);
		extern svr_endgame_t svr_endgame;

		typedef int (*set_world_coords_t)(game::Vector3* vec, game::Entity* entitiy);
		extern set_world_coords_t set_world_coords;

		typedef void (*transform_world_t)(void* worldMatrix, game::Vector3* vec, game::Vector3* screenPos);
		extern transform_world_t transform_world;

		typedef int (*convert_world_to_screen_t)(game::Vector3* vec);
		extern convert_world_to_screen_t convert_world_to_screen;

		typedef int (*get_distance_t)(int x, int y, int z);
		extern get_distance_t get_distance;

		// Variables
		extern IDirect3DDevice9* d3d_device;
		extern HWND* hwnd;
		extern int* frames_per_second;
		extern void* game_res;
		extern void* font;
		extern uint32_t* is_host;
		extern ServerStruct** server;
		extern int* model_count;
		extern Entity** organics;
		extern Entity** vehicles;
		extern Entity** buildings;
		extern Entity** markers;
		extern void* world_matrix;
		extern Entity** local_player;
	}

	// Everything below here is our custom functions that are bascially wrappers around the internal functions/variables

	enum EntityType
	{
		EntityType_Organic,
		EntityType_Vehicle,
		EntityType_Building,
		EntityType_Marker
	};

	int rgb_color(int r, int g, int b);

	void draw_box(BoxBounds bounds, std::string title);
	void draw_text(int x, int y, std::string text, int color);
	void draw_text(Entity* entity, std::string text, int color);
	int get_fps();
	HWND get_hwnd();
	IDirect3DDevice9* get_d3d_device();
	bool is_host();
	ServerStruct* get_server();
	int get_model_count();
	void punt_player(int index);
	Entity* get_entity(EntityType type, int index);
	bool world_to_screen(Vector3* screenPosition, Entity* entity);
	int get_distance_meters(Entity* a, Entity* b);
	Entity* get_local_player();
}