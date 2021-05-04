#include "actor/liquid.h"

#include "tilemgr.h"
#include "actormgr.h"
#include "eventmgr.h"
#include "misctemp.h"

// TODO: wtf

class EventWaves {
public:
    f32 flatHeight;
    f32 waveHeight;
    u32 waveSpeed;
    u8 eventId;

    void init(TerrainEffects* terrain, f32 flatHeight, f32 animSpeed, u8 eventId);
    void update(TerrainEffects* terrain);
};

class CustomWater : public Water {
public:
    EventWaves waves;

    u32 updateWaveEvents();
};

class CustomPoison : public Poison {
public:
    EventWaves waves;

    u32 updateWaveEvents();
};

void EventWaves::init(TerrainEffects* terrain, f32 flatHeight, f32 animSpeed, u8 eventId) {
    terrain->waveAnimSpeed = (u32)(animSpeed * 0x80000000 / 180);
    terrain->waveAnimHeight = 1.55;
    this->flatHeight = flatHeight;
    this->eventId = eventId;

    if (eventId) {
        waveHeight = terrain->waveHeight;
        waveSpeed = terrain->waveSpeed;
        if (!(EventMgr::instance->events & (1 << (eventId - 1)))) {
            terrain->waveHeight = flatHeight;
            terrain->waveSpeed = 0;
        }
    }
}

void EventWaves::update(TerrainEffects* terrain) {
    if (eventId) {
        f32 targetHeight = flatHeight;
        u32 targetSpeed = 0;
        
        if (EventMgr::instance->events & (1 << (eventId - 1))) {
            targetHeight = waveHeight;
            targetSpeed = waveSpeed;
        }

        moveFloatTo(&terrain->waveHeight, targetHeight, 0.4);
        moveValueTo(&terrain->waveSpeed, targetSpeed, 0x20000);
    }
}

u32 CustomWater::updateWaveEvents() {
    waves.update(&terrain);

    return EnvTerrain::onExecute();
}

u32 CustomPoison::updateWaveEvents() {
    waves.update(&terrain);

    return EnvTerrain::onExecute();
}

void initWaterWaves(EnvTerrain* water, Vec3* pos, f32 width, bool noLoc, bool layer0, TerrainEffects::TerrainType type, sead::Heap* heap) {
    water->terrain.init(pos, width, noLoc, layer0, type, heap);
    if (water->settings2 & 1) {
        u32 waveHeight = (water->settings2 >> 20) & 0xF;
        u32 waveSpeed = (water->settings2 >> 4) & 0xF;

        water->terrain.setWaveValues(waveHeight, 0, waveSpeed, 0, 0, 0);
        water->terrain.type = type;

        TileMgr::instance->hasWaves = true;

        u8 eventId = (water->settings2 >> 8) & 0xFF;
        if (type == TerrainEffects::Water) {
            TileMgr::instance->waveType = 2;
            ((CustomWater*)water)->waves.init(&water->terrain, 1.0, 8.0, eventId);
        } else if (type == TerrainEffects::Poison) {
            TileMgr::instance->waveType = 3;
            ((CustomPoison*)water)->waves.init(&water->terrain, 0.8, -4.0, eventId);
        }
    }
}

void updateWaterWaves(TerrainEffects* effects) {
    if (TileMgr::instance->waveType == 2 || TileMgr::instance->waveType == 3) {
        effects->updateWaveCollisions();
    }
}

// u32 updateWavePlatforms() {
//     BaseActor** platform = ActorMgr::instance->findActorByType(ProfileId::Sprite521, ActorMgr::instance->actorList.first);
//     while (platform != ActorMgr::instance->actorList.last) {
//         (*platform)->onExecute();
//         platform = ActorMgr::instance->findActorByType(ProfileId::Sprite521, platform + 1);
//     }
// 
//     return 1;
// }
