#include "log.h"
#include "tilemgr.h"
#include "actor/liquid.h"

void Waves_onCreate(EnvTerrain* _this) {
    // Initialize TerrainEffects but we skip because it's already initialized in Water::onCreate()
  ////_this->effects.init(&_this->position, 57600.0f, true, false, TerrainEffects::Water, _this->_11A40);

    // Set wave values from spritedata but we skip it because it does nothing for some reason
  ////_this->effects.setWaveValues(_this->settings2 >> 4 & 0xF, _this->settings2 >> 0x10 & 0xF, _this->settings2 >> 8 & 0xF, _this->settings2 >> 0x14 & 0xF, _this->settings2 >> 0xC & 0xF, _this->settings2 >> 0x18 & 0xF); 

    // Set top but we skip it because it's not required apparently (or is already set)
  ////_this->setTop(_this->_1AAC - _this->_1AC8);

    // Set type but we skip it because it's already set correctly
  ////_this->effects._E4 = TerrainEffects::Water;

    // TileMgr setup but we skip it because it's not required apparently (or is already set)
  ////TileMgr::instance->hasWaves = true;
  ////TileMgr::instance->waveType = 2;
}

void Waves_onExecute(TerrainEffects* _this) {   // TerrainEffects* part of onExecute because calling the subclass doesn't work for some reason

    // Update wave collisions but we skip it because it already gets called in EnvTerrain::onExecute()
  ////_this->updateWaveCollisions();

    // Check mario wave hit but we skip it because it treats the waves as lava so we do a:
    // TODO: Patch this function to treat water waves as water type
    //_this->checkMarioWaveHit();

    // Set some values for testing
    //? Values have to be set in onExecute for some reason... probably related to this being a TerrainEffects* instead of an EnvTerrain*
  //LOG("val: %x\n", _this->_CC);
    _this->_C4 = 0x1;   // ripple speed
    _this->_C8 = 0xFFFFFF;   // horizontal speed
    _this->_D8 = 0x1AFFFF0; // wave frequency
    _this->_DC = 17;   // height
    _this->_E0 = 0x35;  // peaks height
    _this->_D4 = 0xF;
}
