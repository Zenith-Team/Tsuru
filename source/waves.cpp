#include "log.h"
#include "tilemgr.h"
#include "actor/liquid.h"

void Waves_onCreate(EnvTerrain* _this) {
    LOG("Waves_onCreate");

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

    LOG("waveSpeed: %x\n", _this->effects._C4);
    LOG("waveAnimSpeed: %x\n", _this->effects._C8);
    LOG("waveHeight: %x\n", _this->effects._DC);
    LOG("waveAnimHeight: %x\n", _this->effects._E0);
    LOG("type: %x\n", _this->effects._E4);
}

void Waves_onExecute(TerrainEffects* _this) {
    LOG("Waves_onExecute");

    // Update wave collisions
    _this->updateWaveCollisions();

    LOG("waveHeight: %x\n", _this->_DC);
    // Set some values
    //_this->_C4 *= 3;            // 
    //_this->_C8 = 10;
    _this->_DC = 10;    // waveHeight
    //_this->_E0 *= 3;            // 
}
