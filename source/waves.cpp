#include "game/actor/stage/envterrain.h"
#include "game/tilemgr.h"

void setWaterWaveValues(EnvTerrain* _this) {
    // Wave values
    if (_this->settings2 >> 0x8 & 0x1) { // Nybble 18
        _this->effects.waveRippleSpeed      = 0x10;
        _this->effects.waveHorizontalSpeed  = 0xFFFFFF;
        _this->effects.waveWidth            = 0x1AFFFF0;
        _this->effects._DC                  = 0x11;
        _this->effects.waveRippleHeight     = 0x35;
        _this->effects.waveRippleCount      = 0xFF;
    }

    // Wave collision
    TileMgr::instance()->hasWaves = true;
    TileMgr::instance()->waveType = TileMgr::WaveType_Water;
    _this->effects.updateWaveCollisions();
}

// For some reason the game hangs if we call EnvTerrain::onExecute directly so this is a hack
extern u32 (*onExecute__10EnvTerrainFv)(EnvTerrain*);

u32 Poison_onExecute(EnvTerrain* _this) { // Replaces poison water onExecute()
    // Wave values
    if (_this->settings2 >> 0x8 & 0x1) { // Nybble 18
        _this->effects.waveRippleSpeed      = 0x10;
        _this->effects.waveHorizontalSpeed  = 0xFFFFFF;
        _this->effects.waveWidth            = 0x1AFFFF0;
        _this->effects._DC                  = 0x11;
        _this->effects.waveRippleHeight     = 0x35;
        _this->effects.waveRippleCount      = 0xFF;
    }

    // Wave collision
    TileMgr::instance()->hasWaves = true;
    TileMgr::instance()->waveType = TileMgr::WaveType_Poison;
    _this->effects.updateWaveCollisions();

    return onExecute__10EnvTerrainFv(_this);
}

u32 Quicksand_onExecute(EnvTerrain* _this) { // Replaces quicksand onExecute()
    if (_this->settings2 >> 0x8 & 0x1) {
        _this->effects.waveRippleSpeed      = 0x10;
        _this->effects.waveHorizontalSpeed  = 0xFFFFFF;
        _this->effects.waveWidth            = 0x1AFFFF0;
        _this->effects._DC                  = 0x11;
        _this->effects.waveRippleHeight     = 0x35;
        _this->effects.waveRippleCount      = 0xFF;
    }

    // Wave collision
    TileMgr::instance()->hasWaves = true;
    TileMgr::instance()->waveType = TileMgr::WaveType_Quicksand;
    _this->effects.updateWaveCollisions();

    return onExecute__10EnvTerrainFv(_this);
}
