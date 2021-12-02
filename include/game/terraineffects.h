#pragma once

#include "types.h"

class TerrainEffectsRenderer;

class TerrainEffects { // Size: 0xFF4C
    // This class seems to handle distortions such as the waves in liquids, and the distortion on the bump-from-bottom platform (sprite 407)
    // It is present as a member of EnvTerrain
public:
    enum TerrainType {
        TerrainType_Water     = 0,
        TerrainType_Lava      = 1,
        TerrainType_Poison    = 2,
        TerrainType_LavaWaves = 3,
        TerrainType_Quicksand = 4
    };

    TerrainEffects();
    ~TerrainEffects(); // nullsub

    virtual void vfC();  // deleted
    virtual void vf10(); // deleted

    void playerLavaWaveBurn();
    void updateWaveCollisions();

    TerrainEffectsRenderer* renderer;
    u8 _4[4]; // Unknown values
    Vec3f _8;
    u8 _14[12];
    Vec3f _20;
    u8 _2C[48];
    u8 _5C[48];
    u8 _8C[4]; // Unknown values
    f32 _90;
    u32 _94;
    f32 _98;
    f32 _9C;
    u32 _A0;
    u32 _A4;
    u32 _A8;
    s32 _AC;
    u32 _B0;
    u32 _B4;
    u32 _B8;
    u32 _BC;
    u32 _C0;
    u32 waveRippleSpeed;
    u32 waveHorizontalSpeed;
    u32 _CC;
    u32 __D0;
    u32 waveRippleCount;
    u32 waveWidth;
    f32 _DC;
    f32 waveRippleHeight;
    u8 _E4;
    u8 _E5;
    u8 _E6[0xFE58]; // Inlined struct
    u32 _FF40;
    u8 _FF44[4]; // Unknown values
};

static_assert(sizeof(TerrainEffects) == 0xFF4C, "TerrainEffects size mismatch");
