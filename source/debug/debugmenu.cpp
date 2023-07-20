#include "game/actor/actormgr.h"
#include "sead/heapmgr.h"
#include "sead/scopedlock.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "game/wrappedcontroller.h"
#include "log.h"

#include "imgui/imgui.h"

extern "C" u32 expHeapVtable[];
extern "C" u32 frameHeapVtable[];
extern "C" u32 unitHeapVtable[];
extern "C" u32 separateHeapVtable[];

char logBuffer[2048];

void printToDebugMenu(const char* msg) {
    static char bufferBuffer[2048];

    s32 length = strlen(msg);
    memset(bufferBuffer, 0, sizeof(bufferBuffer));

    for (s32 i = 0; i < sizeof(logBuffer); i++) {
        if ((i - length) < 0) {
            continue;
        }

        bufferBuffer[i - length] = logBuffer[i];
    }

    memcpy(logBuffer, bufferBuffer, sizeof(logBuffer));
    memcpy(logBuffer + (sizeof(logBuffer) - length), msg, length);
}

void drawMgrs();
void drawHacks();
void drawDebug();

void drawHeapImGui(const sead::Heap* heap);
void drawActorImGui(Actor* actor);
void drawHeapMgrImGui();
void drawActorMgrImGui();

/** MAIN: */

void tsuruDebugMenu() {
    static WrappedController gamepad;
    static bool inited = false;

    if (!inited) {
        gamepad.init(4); // Gamepad

        inited = true;
    }

    static bool show = false;
    static bool held = false;
    static bool prevHeld = false;
    static u32 counter = 0;

    held = nthBit32Right(gamepad.padHold.bits, 0xB); // Minus button

    if (held) {
        if (!prevHeld) {
            show = false;
            counter = 0;
        }

        counter++;

        if (counter == 60 * 3) {
            show = true;
        }
    } else {
        counter = 0;
    }

    prevHeld = held;

    if (show) {
        drawMgrs();
        drawHacks();
        drawDebug();
    }
}

/** MENUS: */

static void drawMgrs() {
    ImGui::SetNextWindowPos(ImVec2(914.0f, 10.0f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(355.0f, 700.0f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Mgr's Info")) {
        drawHeapMgrImGui();

        if (ActorMgr::instance()) {
            drawActorMgrImGui();
        }
    }
    ImGui::End();
}

static void drawHacks() {
    ImGui::SetNextWindowPos(ImVec2(16.0f, 200.0f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(176.0f, 135.0f));
    if (ImGui::Begin("Hacks")) {
        ImGui::Checkbox("Infinite Lives", &TsuruSaveMgr::sSaveData.infiniteLivesEnabled);
        ImGui::Checkbox("Infinite Time", &TsuruSaveMgr::sSaveData.infiniteTimeEnabled);
        ImGui::Checkbox("No Clip", &TsuruSaveMgr::sSaveData.noClipEnabled);
        ImGui::Checkbox("Invincibility", &TsuruSaveMgr::sSaveData.invincibilityEnabled);
    }
    ImGui::End();
}

static void drawDebug() {
    ImGui::SetNextWindowPos(ImVec2(14.0f, 347.0f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(342.0f, 365.0f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Debug Tools")) {
        ImGui::Checkbox("Collision Viewer", &TsuruSaveMgr::sSaveData.collisionViewerEnabled);

        if (ImGui::CollapsingHeader("Log Console"), ImGuiTreeNodeFlags_DefaultOpen) {
            if (ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar)) {
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

                const char* lineStart = logBuffer + sizeof(logBuffer);
                while (*lineStart != '\0') {
                    lineStart--;
                }
                lineStart++;

                for (u32 i = 0; i < sizeof(logBuffer); i++) {                
                    if (logBuffer[i] == '\n') {
                        ImGui::TextUnformatted(lineStart, &logBuffer[i]);
                        lineStart = &logBuffer[i+1];
                    }
                }

                ImGui::PopStyleVar();

                if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
                    ImGui::SetScrollHereY(1.0f);
                }
            } ImGui::EndChild();
        }
    }
    ImGui::End();
}

/** INTERNAL: */

static void drawHeapImGui(const sead::Heap* heap) {
    const char* type = "???";

    u32* vtable = *(u32**)(((u8*)heap) + 0xC);

    if (vtable == expHeapVtable)
        type = "ExpHeap";
    else if (vtable == frameHeapVtable)
        type = "FrameHeap";
    else if (vtable == unitHeapVtable)
        type = "UnitHeap";
    else if (vtable == separateHeapVtable)
        type = "SeparateHeap";

    //FormatFixedSafeString<128> buf("%s: %s###%d", heap->getName().cstr(), type, heap);

    char buf[128] = { 0 };
    __os_snprintf(buf, 128, "%s: %s###%d", heap->getName().cstr(), type, heap);

    if (ImGui::TreeNode(buf)) {
        const char* dir = heap->direction == sead::Heap::HeapDirection_Forward ? "Forward" : "Reverse";

        ImGui::Text("Address: 0x%X", heap->start); // getStartAddress() is deleted in ExpHeap vtable
        ImGui::Text("Size: 0x%X", heap->size); // getSize() is deleted in some heaps vtable
        ImGui::Text("FreeSize: 0x%X", heap->getFreeSize());
        ImGui::Text("MaxAllocSize: 0x%X", heap->getMaxAllocatableSize(sizeof(void*)));
        ImGui::Text("Direction: %s", dir);
        //ImGui::Text("Freeable: %s", heap->isFreeable() ? "True" : "False");
        //ImGui::Text("Resizable: %s", heap->isResizable() ? "True" : "False");
        //ImGui::Text("Adjustable: %s", heap->isAdjustable() ? "True" : "False");
        //ImGui::Text("Empty: %s", heap->isEmpty() ? "True" : "False");

        if (heap->children.count > 0) {
            ImGui::Text("Children: %d", heap->children.count);

            for (sead::OffsetList<sead::Heap>::iterator it = heap->children.begin(); it != heap->children.end(); ++it) {
                drawHeapImGui(&*it);
            }
        } else {
            ImGui::Text("Children: 0");
        }

        ImGui::TreePop();
    }
}

static void drawHeapMgrImGui() {
    sead::ScopedLock<sead::CriticalSection> lock(sead::HeapMgr::sHeapTreeLockCS);

    if (ImGui::CollapsingHeader("sead::HeapMgr")) {
        for (u32 i = 0; i < sead::HeapMgr::sRootHeaps.ptrNum; i++) {
            drawHeapImGui((sead::Heap*)sead::HeapMgr::sRootHeaps.ptrs[i]);
        }
    }
}

static void drawProfileImGui(const Profile* profile) {
    //FormatFixedSafeString<64> buf("profile: %d###%d", profile->id, profile);

    char buf[64] = { 0 };
    __os_snprintf(buf, 64, "Profile: %d###%d", profile->id, profile);

    if (ImGui::TreeNode(buf)) {
        ImGui::Text("BuildFunc: 0x%X", profile->buildFunc);
        ImGui::Text("Priority: %i", profile->getPriority(profile->id));

        ImGui::TreePop();
    }
}

static void drawActorImGui(Actor* actor) {
    //FormatFixedSafeString<128> buf("0x%08X###%d", actor->id, actor);

    char buf[128] = { 0 };
    __os_snprintf(buf, 128, "0x%08X###%d", actor->id, actor);

    if (ImGui::TreeNode(buf)) {
        drawHeapImGui(actor->heap);
        drawProfileImGui(actor->profile);

        ImGui::Text("WasNotDeferred: %s", actor->wasNotDeferred ? "True" : "False");
        ImGui::Text("IsCreated: %s", actor->isCreated ? "True" : "False");
        ImGui::Text("IsDeleted: %s", actor->isDeleted ? "True" : "False");

        ImGui::SameLine();
        if (ImGui::SmallButton("delete")) {
            actor->isDeleted = true;
        }

        ImGui::Text("Settings1: 0x%08X", actor->settings1);
        ImGui::Text("Settings2: 0x%08X", actor->settings2);

        ImGui::Text("Children Count: %d", actor->childList.count);

        if (actor->parent) {
            ImGui::Text("Parent: 0x%08X", actor->parent->id);
        } else {
            ImGui::Text("Parent: nullptr");
        }

        StageActor* stageActor = sead::DynamicCast<StageActor>(actor);
        if (stageActor) {
            ImGui::DragFloat3("Position", &stageActor->position.x);
            ImGui::DragFloat3("Speed", &stageActor->speed.x);
            ImGui::DragFloat3("MaxSpeed", &stageActor->maxSpeed.x);
            ImGui::DragFloat3("Scale", &stageActor->scale.x);
            ImGui::DragInt3("Rotation", (int*)&stageActor->rotation.x);
        }

        ImGui::TreePop();
    }
}

static void drawActorMgrImGui() {
    if (ImGui::CollapsingHeader("ActorMgr")) {
        ActorMgr* actorMgr = ActorMgr::instance();

        ImGui::Text("Actor Count: %u", actorMgr->activeActors.count + actorMgr->actorsToDelete.count);

        ActorBuffer* actors = &actorMgr->actors;
        for (u32 i = 0; i < actors->start.size; i++) {
            Actor* actor = actors->start[i];
            if (actor) {
                drawActorImGui(actor);
            }
        }
    }
}
