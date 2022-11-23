#include "game/actor/stage/envterrain.h"
#include "game/actor/stage/water.h"
#include "game/actor/stage/poison.h"
#include "game/actor/stage/quicksand.h"
#include "game/tilemgr.h"

const ActorInfo WavyWaterActorInfo = { Vec2i(8, 0), Vec2i(0, 0), Vec2i(128, 128), 0, 0, 0, 0, 4 };
REGISTER_PROFILE(Water, ProfileID::WavyWater, "WavyWater", &WavyWaterActorInfo);
PROFILE_RESOURCES(ProfileID::WavyWater, Profile::LoadResourcesAt::Course, "obj_waterfull", "obj_waterhalf");

const ActorInfo WavyPoisonActorInfo = { Vec2i(8, 0), Vec2i(0, 0), Vec2i(24, 24), 0, 0, 0, 0, 4 };
REGISTER_PROFILE(Poison, ProfileID::WavyPoison, "WavyPoison", &WavyPoisonActorInfo);
PROFILE_RESOURCES(ProfileID::WavyPoison, Profile::LoadResourcesAt::Course, "obj_poisonwater", "obj_magmadeco");

const ActorInfo WavyQuicksandActorInfo = { Vec2i(8, 0), Vec2i(0, 0), Vec2i(128, 128), 0, 0, 0, 0, 4 };
REGISTER_PROFILE(Quicksand, ProfileID::WavyQuicksand, "WavyQuicksand", &WavyQuicksandActorInfo);
PROFILE_RESOURCES(ProfileID::WavyQuicksand, Profile::LoadResourcesAt::Course, "obj_quicksand");

void setWaterWaveValues(EnvTerrain* _this) {
    if (_this->getProfileID() == ProfileID::WavyWater) {
        // Parameters
        _this->effects.waveRippleSpeed     = (_this->eventID1  >> 0x4  & 0xF) * 2 * 2;
        _this->effects.waveHorizontalSpeed = (_this->eventID1          & 0xF) * 1048575 * 2;
        _this->effects.waveWidth           = (_this->eventID2  >> 0x4  & 0xF) * 5767160 * 2;
        _this->effects._DC                 = (_this->eventID2          & 0xF) * 2 * 2;
        _this->effects.waveRippleHeight    = (_this->settings1 >> 0x1C & 0xF) * 3 * 2;
        _this->effects.waveRippleCount     = (_this->settings1 >> 0x18 & 0xF) * 15 * 2;
        _this->effects._CC                 = (_this->settings1 >> 0x14 & 0xF) * 10 * 2;

        // Collision
        TileMgr::instance()->hasWaves = true;
        TileMgr::instance()->waveType = TileMgr::WaveType::Water;
        _this->effects.updateWaveCollisions();
    }
}

// We're not in a class so we must do this manually
extern "C" u32 onExecute__10EnvTerrainFv(EnvTerrain*);

u32 Poison_onExecute(EnvTerrain* _this) { // Replaces poison water onExecute()
    if (_this->getProfileID() == ProfileID::WavyPoison) {
        // Parameters
        _this->effects.waveRippleSpeed     = (_this->eventID1  >> 0x4  & 0xF) * 2 * 2;
        _this->effects.waveHorizontalSpeed = (_this->eventID1          & 0xF) * 1048575 * 2;
        _this->effects.waveWidth           = (_this->eventID2  >> 0x4  & 0xF) * 5767160 * 2;
        _this->effects._DC                 = (_this->eventID2          & 0xF) * 2 * 2;
        _this->effects.waveRippleHeight    = (_this->settings1 >> 0x1C & 0xF) * 3 * 2;
        _this->effects.waveRippleCount     = (_this->settings1 >> 0x18 & 0xF) * 15 * 2;
        _this->effects._CC                 = (_this->settings1 >> 0x14 & 0xF) * 10 * 2;

        // Collision
        TileMgr::instance()->hasWaves = true;
        TileMgr::instance()->waveType = TileMgr::WaveType::Poison;
        _this->effects.updateWaveCollisions();
    }

    return onExecute__10EnvTerrainFv(_this);
}

u32 Quicksand_onExecute(EnvTerrain* _this) { // Replaces quicksand onExecute()
    if (_this->getProfileID() == ProfileID::WavyQuicksand) {
        // Parameters
        _this->effects.waveRippleSpeed     = (_this->eventID1  >> 0x4  & 0xF) * 2 * 2;
        _this->effects.waveHorizontalSpeed = (_this->eventID1          & 0xF) * 1048575 * 2;
        _this->effects.waveWidth           = (_this->eventID2  >> 0x4  & 0xF) * 5767160 * 2;
        _this->effects._DC                 = (_this->eventID2          & 0xF) * 2 * 2;
        _this->effects.waveRippleHeight    = (_this->settings1 >> 0x1C & 0xF) * 3 * 2;
        _this->effects.waveRippleCount     = (_this->settings1 >> 0x18 & 0xF) * 15 * 2;
        _this->effects._CC                 = (_this->settings1 >> 0x14 & 0xF) * 10 * 2;

        // Collision
        TileMgr::instance()->hasWaves = true;
        TileMgr::instance()->waveType = TileMgr::WaveType::Quicksand;
        _this->effects.updateWaveCollisions();
    }

    return onExecute__10EnvTerrainFv(_this);
}
