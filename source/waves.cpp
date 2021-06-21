#include "log.h"
#include "tilemgr.h"
#include "actor/liquid.h"

void Waves_onCreate(EnvTerrain* _this) {
    //LOG("Waves_onCreate");

    // Initialize TerrainEffects but we skip because it's already initialized in Water::onCreate()
    //_this->effects.init(&_this->position, 57600.0f, true, false, TerrainEffects::Water, _this->_11A40);

    // Set wave values from spritedata
    _this->effects.setWaveValues(_this->settings2 >> 4 & 0xF, _this->settings2 >> 0x10 & 0xF, _this->settings2 >> 8 & 0xF, _this->settings2 >> 0x14 & 0xF, _this->settings2 >> 0xC & 0xF, _this->settings2 >> 0x18 & 0xF); 

    // Set top
    _this->setTop(_this->_1AAC - _this->_1AC8);

    _this->effects._E4 = TerrainEffects::Water;   // Set type

    // TileMgr setup
    TileMgr::instance->hasWaves = true;
    TileMgr::instance->waveType = 2;

    _this->effects._E0 = 1.55;  // Set waveAnimHeight
    _this->effects._DC = 1.0;   // Set waveHeight

    //LOG("TileMgr", TileMgr::instance);
}

void Waves_onExecute(EnvTerrain* _this) {
    //LOG("Waves_onExecute");

    // Update wave collisions but it crashes so we skip it
    //_this->effects.updateWaveCollisions();
}
