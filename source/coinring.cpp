#include "game/actor/stage/stageactor.h"
#include "game/eventmgr.h"

extern "C" void RingActivateCustom(StageActor* self) {
    u32 time = 0x3C; // default value
    bool b = *((u32*)(((u32)self)+0x17C8)) == 1;

    if (self->settings2 != 0) {
        time = self->settings2;
    } else if (b) {
        time = 0x18;
    }

    EventMgr::instance()->set((self->eventID2 - 1) & 0xFF, time, true, 0, 1, 0, b);
}
