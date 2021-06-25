#pragma once

#include "sead.h"
#include "actor/multistateactor.h"

class TerrainEffects {  // size: 0xFF4C
public:
	enum TerrainType {
		Water = 0,
		Lava = 1,
		Poison = 2,
		LavaWaves = 3,
		QuickSand = 4
	};

	u32 _0;					// 0		//? Newer U: void* renderer
	u8 unk1[4];				// 4
	Vec3 _8;				// 8
	u8 unk2[12];			// 14
	f32 _20;				// 20		//? This could be a Vec3 along with the two members below but I haven't looked into it further
	f32 _24;				// 24		
	u8 unk3[100];			// 28
	f32 _8C;				// 8C
	f32 _90;				// 90		//? Newer U: u32
	u32 _94;				// 94
	f32 _98;				// 98		//? Newer U: u32
	f32 _9C;				// 9C		//? Newer U: u32
	u32 _A0;				// A0
	u32 _A4;				// A4
	u32 _A8;				// A8
	u32 _AC;				// AC
	u32 _B0;				// B0
	u32 _B4;				// B4
	u32 _B8;				// B8
	u32 _BC;				// BC
	u32 _C0;				// C0
	u32 _C4;				// C4		//? Newer U: waveSpeed				// Suggested name: rippleSpeed
	u32 _C8;				// C8		//? Newer U: waveAnimSpeed			// Suggested name: horizontalSpeed
	u32 _CC;				// CC
	u32 _D0;				// D0
	u32 _D4;				// D4		//? Newer U: waveWidth				// Suggested name: rippleCount or rippleWidth (Suggested range unknown)
	u32 _D8;				// D8		//? Newer U: waveType				// Suggested name: waveFrequency/waveWidth (Suggested range unknown)
	f32 _DC;				// DC		//? Newer U: waveHeight
	f32 _E0;				// E0		//? Newer U: waveAnimHeight			// Suggested name: peakHeight or rippleHeight
	u8 _E4;					// E4		//? Newer U: type
	u8 _E5;					// E5		//? Newer U: noLocation
	u8 unk4[65114];			// E6		//? Newer U: data
	u32 _FF40;				// FF40
	u8 unk5[4];				// FF44
	void* effectsVtable;	// FF48

	void init(Vec3* pos, float width, bool noLoc, bool layer0, TerrainType type, sead::Heap* heap);
	void setWaveValues(u32, u32, u32, u32, u32, u32);	//? Newer U param names were weird so I removed them for now
	void updateWaveCollisions();
	void checkMarioWaveHit();
	void someUpdateFunctionMaybe();
};

class EnvTerrain : public MultiStateActor {  // size: 0x11A78
public:
	void* modelOrModelWrapper;		// 17C8
	u8 unk1[8];						// 17CC
	f32 _17D4;						// 17D4
	u8 unk2[8];						// 17D8
	f32 _17E0;						// 17E0
	u8 unk3[16];					// 17E4
	void* _17F4; 					// 17F4 	//? some vtable		
	u8 unk4[160];					// 17F8
	f32 _1898;						// 1898
	u8 unk5[520];					// 189C
	u32 _1AA4;						// 1AA4
	u32 _1AA8;						// 1AA8
	f32 _1AAC;						// 1AAC
	f32 _1AB0;						// 1AB0
	f32 _1AB4;						// 1AB4 	//? Newer U: riseTop
	f32 _1AB8;						// 1AB8
	f32 _1ABC;						// 1ABC
	f32 _1AC0;						// 1AC0
	f32 _1AC4;						// 1AC4 	//? Newer U: risingSpeed
	f32 _1AC8;						// 1AC8		//? Suggested name: currentHeightNegative
	f32 _1ACC;						// 1ACC 	//? Newer U: currentHeight    Suggested name: currentHeightPositive
	u32 _1AD0;						// 1AD0
	u32 _1AD4;						// 1AD4
	u16 _1AD8;						// 1AD8
	u16 _1ADA;						// 1ADA 	//? Newer U: loweringDelay
	bool onlyRenderWaves;			// 1ADC
	u8 _1ADD;						// 1ADD
	u8 _1ADE;						// 1ADE
	u8 _1ADF;						// 1ADF
	u32 _1AE0;						// 1AE0
	TerrainEffects effects;			// 1AE4
	sead::IDisposer disposer;		// 11A30
	u32 _11A40;						// 11A40	//? Newer U: sead::Heap* additionalHeap
	u8 unk6[4];						// 11A44
	u32 _11A48;						// 11A48	//? Newer U: u64 eventMask
	u32 _11A4C;						// 11A4C
	u32 _11A50;						// 11A50
	u32 _11A54;						// 11A54
	u32 _11A58;						// 11A58	//? Newer U: u64 eventMask2
	u32 _11A5C;						// 11A5C
	u32 _11A60;						// 11A60
	f32 _11A64;						// 11A64	//? Newer U: risingHeight
	f32 _11A68;						// 11A68
	u32 _11A6C;						// 11A6C
	u16 _11A70;						// 11A70
	u8 _11A72;						// 11A72
	u8 _11A73;						// 11A73
	u8 unk7[4];						// 11A74

	u32 onExecute() override;

	void setTop(f32 top);
};
