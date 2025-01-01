#pragma once

namespace game
{
	// Internal game structures belong here

	struct Vector3
	{
		int32_t x;
		int32_t y;
		int32_t z;
	};

	typedef uint32_t ActionType;
	typedef uint32_t EntityState;

	enum ItemType
	{
		ItemType_Vehicle = 0x1,
		ItemType_DecFol = 0x2,
		ItemType_Person = 0x3,
		ItemType_Marker = 0x4,
		ItemType_Building = 0x5,
		ItemType_PowObj = 0x6,
		ItemType_Effect = 0x8,
	};


	struct BoxBounds
	{
		uint32_t x1;
		uint32_t y1;
		uint32_t x2;
		uint32_t y2;
	};

	struct Position
	{
		int32_t x;
		int32_t y;
		int32_t z;
		int32_t yaw;
		int32_t pitch;
		int32_t roll;
	};

	struct WeaponDefinition
	{
		uint32_t category;
		uint32_t rank;
		uint32_t statId;
		uint32_t clipSize;
		uint32_t startRounds;
		char pad_0014[16];
		uint32_t roundType;
		char pad_0028[28];
		uint32_t attackAnim;
		char pad_0048[116];
		float renderFov;
		char pad_00C0[632];
	};

	struct ItemDefinition
	{
		char name[30];
		char pad_001E[18];
		uint32_t id;
		uint32_t attributes;
		ItemType type;
		char graphic[16];
		char husk[16];
		char pad_005C[64];
		char animDef[16];
		char pad_00AC[176];
		uint16_t hp;
		char pad_015E[550];
		char soundDeath[16];
		char pad_0394[1060];
	};

	struct AI;
	struct WeaponSlot;

	struct Entity
	{
		uint32_t itemDefinitionIndex;;
		char pad_0004[4];
		Position position;
		EntityState state;
		ItemDefinition* itemDefinition;
		char pad_0028[16];
		AI* ai;
		char pad_003C[16];
		uint32_t ssn;
		char pad_0050[4];
		Position N00000136;
		char pad_006C[24];
		int32_t lean;
		char pad_0088[64];
		char name[15];
		char pad_00D7[5];
		WeaponSlot* weaponSlot;
		char pad_00E0[2];
		int16_t health;
		char pad_00E4[18];
		uint8_t team;
		char pad_00F7[69];
		Entity* onEntity;
		char pad_0140[36];
		ActionType action;
		char pad_0168[16];
		uint32_t weaponDefinitionIndex;
		char pad_017C[64];
		uint32_t stance;
		char pad_01C0[36];
		Entity* lookingAtEntity;
		char pad_01E8[92];
		uint32_t characterType;
		char pad_0248[84];
	};

	struct WeaponSlot
	{
		char pad_0000[24];
		uint32_t currentRounds;
		char pad_001C[28];
		WeaponDefinition* weaponDefinition;
		Entity* entity;
		char pad_0040[32];
	};

	struct AI
	{
		Entity* entity;
		char pad_0004[338];
		int16_t previousIndex;
		int16_t currentIndex;
		char pad_015A[42];
	};

	struct unknown_struct02;

	struct unknown_struct05
	{
		unknown_struct02* N00058B6E;
		unknown_struct05* N00058B6F;
		unknown_struct05* N00058B70;
		char pad_000C[8];
		uint16_t length;
		uint8_t opcode;
		char pad_0017[5];
		uint8_t buffer[640];
	};


	struct unknown_struct02
	{
		unknown_struct05* N00058B36;
		unknown_struct05* N00058B37;
		uint32_t N00058B38;
		unknown_struct05* might_be_wrong;
		char pad_0010[28];
		unknown_struct05 N00058B41[1024];
		char pad_A702C[36];
	};

	struct ServerPlayerStruct
	{
		char pad_0000[8];
		ServerPlayerStruct* nextPlayer;
		uint32_t index;
		char pad_0010[8];
		Entity* entity;
		char name[16];
		char pcid[16];
		char pad_003C[84];
		uint8_t team;
		char pad_0091[3];
		uint32_t N00056A90;
		char pad_0098[28];
		uint32_t breathTicks;
		char pad_00B8[26600];
		uint32_t characterType;
		char pad_68A4[32];
		bool inUse;
		bool isHost;
		char pad_68C6[158];
		unknown_struct02 N000584C4;
		char pad_AD9B4[216];
		int32_t suicides;
		int32_t friendlyKills;
		int32_t kills; //0xADA94
		int32_t deaths; //0xADA98
		char pad_ADA9C[5008]; //0xADA9C
		uint16_t delayTickCount; //0xAEE2C
		uint16_t N00060C31; //0xAEE2E
		uint16_t currentDelayTick; //0xAEE30
		char pad_AEE32[2]; //0xAEE32
		uint32_t ticks; //0xAEE34
		uint32_t N000589E9; //0xAEE38
		char pad_AEE3C[1140]; //0xAEE3C
		uint32_t heartbeatCount; //0xAF2B0
		char pad_AF2B4[84];
		uint32_t lastMessageTicks;
		char pad_AF30C[48];
	};

	struct ServerStruct
	{
		int32_t maxPlayerCount;
		ServerPlayerStruct* playersPtr;
		char pad_0008[24];
		ServerPlayerStruct players[1];
	};
}