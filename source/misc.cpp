#include "game/task/taskmgr.h"
#include "game/task/coursetask.h"
#include "game/level/levelinfo.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "sead/graphicscontext.h"
#include "sead/controllermgr.h"
#include "sead/heapmgr.h"
#include "game/wrappedcontroller.h"
#include "game/actor/actor.h"
#include "game/actor/actormgr.h"
#include "game/playermgr.h"
#include "log.h"

fmt::_Hex fmt::hex;
bool fmt::_hexActive = false;

extern "C" {

void* memcpy(void* dst, const void* src, size_t size) {
    return OSBlockMove(dst, src, size, 0);
}

int printf(const char*, ...) {
    return 0;
}

int sprintf(char* buffer, const char* format, ...) {
  va_list va;
  va_start(va, format);
  const int ret = vsnprintf(buffer, (size_t)-1, format, va);
  va_end(va);
  return ret;
}

void* memset(void* dst, int value, size_t size) {
    return OSBlockSet(dst, value, size);
}

void* malloc(size_t size) {
    return MEMAllocFromDefaultHeap(size);
}

void* memalign(size_t align, size_t size) {
    return MEMAllocFromDefaultHeapEx(size, align);
}

void free(void* ptr) {
    return MEMFreeToDefaultHeap(ptr);
}

#define isdigit(c) (c >= '0' && c <= '9')

double atof(const char* s) {
    double a = 0.0;
    int e = 0;
    int c;
    while ((c = *s++) != '\0' && isdigit(c)) {
        a = a * 10.0 + (c - '0');
    }
    if (c == '.') {
        while ((c = *s++) != '\0' && isdigit(c)) {
            a = a * 10.0 + (c - '0');
            e = e - 1;
        }
    }
    if (c == 'e' || c == 'E') {
        int sign = 1;
        int i = 0;
        c = *s++;
        if (c == '+')
            c = *s++;
        else if (c == '-') {
            c = *s++;
            sign = -1;
        }
        while (isdigit(c)) {
            i = i * 10 + (c - '0');
            c = *s++;
        }
        e += i * sign;
    }
    while (e > 0) {
        a *= 10.0;
        e--;
    }
    while (e < 0) {
        a *= 0.1;
        e++;
    }
    return a;
}

double log(double d) {
    return logf(d);
}

}

extern "C" void respawn(u32 _this, sead::TaskBase* currentTask, sead::TaskClassID& targetTask, u32 r6) {
    if (TsuruSaveMgr::sSaveData.instantRespawnEnabled && r6 == 0x30009 && !PlayerMgr::instance()->players[0]->input.getButtonJump()) {
        TaskMgr::instance()->startLevel(CourseTask::instance(), LevelInfo::instance()->world, LevelInfo::instance()->level);
    } else {
        TaskMgr::instance()->changeTask(currentTask, targetTask, r6, 0);
    }
}

// Always a copy of the currently applied graphics context
// NEVER write to this, only read
volatile sead::GraphicsContext CurrentGraphicsContext;

#ifdef TARGET_TRICKY
static const RegisterProfile<Actor> __profifle_Actor(0x135);
PROFILE_RESOURCES(0x135, Profile::LoadResourcesAt::Course, "kuribo");

REGISTER_PROFILE(Actor, Profile::spriteToProfileList[479]);
PROFILE_RESOURCES(Profile::spriteToProfileList[479], Profile::LoadResourcesAt::Course, "kuribo");
#endif

Actor* ActorMgr::instanciateActor(const ActorBuildInfo& buildInfo, bool dontDefer) {
    Actor* actor = nullptr;
    sead::Heap* actorHeap = nullptr;

    u32 id = buildInfo.profile->id;
    if (id == 0x1BC || id == 0x1BB || id == 0x356 || id == 0x357) // Add extra profile ids here
        actorHeap = sead::FrameHeap::tryCreate(0, "PlayerHeap", this->playerUnitHeap, sead::Heap::HeapDirection_Forward, false);
    else
        actorHeap = sead::FrameHeap::tryCreate(0, "ActorHeap", this->actorUnitHeap, sead::Heap::HeapDirection_Forward, false);

    if (actorHeap) {
        this->currentID = this->actors.end.size << 0x16 | this->actors._10;
        this->currentWasNotDeferred = dontDefer;

        sead::CurrentHeapSetter currentHeap(actorHeap);

        actor = buildInfo.profile->buildFunc(&buildInfo);

        this->actors.addActor(actor);
    }

    return actor;
}
