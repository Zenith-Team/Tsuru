#include "log.h"
#include "terrain.h"

void initWaves(EnvTerrain* _this) {
    //// LOG("initWaves function called");

    // Initialize TerrainEffects
    _this->effects.init(&_this->position, 57600.0f, true, false, TerrainEffects::Water, _this->_11A40);

    // Set wave values from spritedata
    _this->effects.setWaveValues(_this->settings2 >> 4 & 0xF, _this->settings2 >> 0x10 & 0xF, _this->settings2 >> 8 & 0xF, _this->settings2 >> 0x14 & 0xF, _this->settings2 >> 0xC & 0xF, _this->settings2 >> 0x18 & 0xF); 
}
