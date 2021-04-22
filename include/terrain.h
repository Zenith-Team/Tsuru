#pragma once

#include "actor/actormultistate.h"
#include "activecollider.h"

// TODO: verify

class TerrainEffects {  // TODO: Incomplete
public:
	enum TerrainType {
		Water = 0,
		Lava = 1,
		Poison = 2,
		LavaWaves = 3,
		QuickSand = 4
	};
    

	void *renderer;
	u32 _4;			
	Vec3 position;	
	u8 _14[12];				
	Vec3 _20;		
	u8 _2C[48];		
	u8 _5C[48];		
	u32 width;		
	u32 _90;		
	u32 _94;		
	u32 _98;		
	u32 _9C;		
	u32 _A0;		
	u32 _A4;		
	u32 _A8;		
	u32 _AC;		
	u32 _B0;		
	u32 _B4;		
	u32 _B8;		
	u32 _BC;		
	u32 _C0;		
	u32 waveSpeed;			
	u32 waveAnimSpeed;			
	u32 _CC;				
	u32 _D0;				
	u32 waveWidth;		
	u32 waveType;			
	f32 waveHeight;			
	f32 waveAnimHeight;	
	u8 type;		
	u8 noLocation;			
	u8 _E6;				
	u8 _E7;				
	u8 data[0xF8F4 + 0x658 - 0xE8];

	void init(Vec3 *pos, float width, bool noLoc, bool layer0, TerrainType type, sead::Heap *heap);
	void setWaveValues(u32 h, u32 eftHeight, u32 spd, u32 anmSpeed, u32 w, u32 eft);		
	void checkMarioWaveHit();
	void updateWaveCollisions();
};

class EnvTerrain : public ActorMultiState {
public:
	u32 _17C8;
	u32 _17CC;
	Vec3 _17D0;
	Vec3 _17DC;
	ActiveCollider collision; //? Not sure if this is actually ActiveCollider, it was labelled "SolidCollider" in Newer U
	u8 _1A78[4 * 8];
	u32 _1A98;
	Vec2 _1A9C;
	u32 _1AA4;
	u32 _1AA8;
	f32 _1AAC;
	f32 _1AB0;
	f32 riseTop;
	f32 _1AB8;
	f32 _1ABC;
	f32 _1AC0;
	f32 risingSpeed;
	f32 _1AC8;
	f32 currentHeight;
	u32 _1AD0;
	u32 _1AD4;
	u16 _1AD8;
	u16 loweringDelay;
	bool onlyRenderWaves;
	u8 _1ADD;
	u8 _1ADE;
	u8 _1ADF;
	u32 _1AE0;
	TerrainEffects terrain;

	sead::IDisposer disposer;
	sead::Heap *additionalHeap;
	u32 _11A44;
	u64 eventMask;
	u32 _11A50;
	u32 _11A54;
	u64 eventMask2;
	u32 _11A60;
	f32 risingHeight;
	f32 _11A68;
	u32 _11A6C;
	u32 _11A70;
	u32 _11A74;

	EnvTerrain(ActorBuildInfo *);
	
	u32 onExecute();

	void setTop(float top);
};
