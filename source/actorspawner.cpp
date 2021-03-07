#include "actor/actor.h"
#include "actormgr.h"
#include "eventmgr.h"

class ActorSpawner : public Actor {
public:
    ActorSpawner(const ActorBuildInfo* buildInfo);
    static Base* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override;

    u16 spawnProfileId;
    bool spawned;
};

const Profile actorSpawnerProfile(&ActorSpawner::build, ProfileId::Sprite436, "ActorSpawner", nullptr, 0);
PROFILE_RESOURCES(ProfileId::Sprite436);


ActorSpawner::ActorSpawner(const ActorBuildInfo* buildInfo) : Actor(buildInfo) { }

Base* ActorSpawner::build(const ActorBuildInfo* buildInfo) {
    return new ActorSpawner(buildInfo);
}

u32 ActorSpawner::onCreate() {
    if (!eventId2)
        return 2;

    u16 inputId = linkId | ((movementId & 0xF) << 8);
    if (movementId & 0x10)
        spawnProfileId = Profile::spriteToProfileList[inputId];
    else
        spawnProfileId = inputId;

    spawned = false;

    onExecute(); //Call onExecute() to prevent the spawned actor to be missing for one frame if the event is alredy active.
    return 1;
}

u32 ActorSpawner::onExecute() {
    if (EventMgr::instance->isActive(eventId2-1)) {
        if (!spawned) {
            ActorBuildInfo buildInfo = { 0 };
            buildInfo.settings1 = settings1;
            buildInfo.settings2 = settings2;
            buildInfo.profile = Profile::get(spawnProfileId);
            buildInfo.position = position;
            buildInfo.eventId1 = eventId1 & 0xF;
            buildInfo.eventId2 = (eventId1 >> 4) & 0xF;
            ActorMgr::instance->create(&buildInfo, 0);

            spawned = true;
        }
    }
    else
        spawned = false;

    return 1;
}
