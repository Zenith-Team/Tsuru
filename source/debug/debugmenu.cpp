#include "game/actor/actormgr.h"
#include "sead/heapmgr.h"
#include "sead/scopedlock.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "game/wrappedcontroller.h"
#include "game/task/taskmgr.h"
#include "game/task/courseselecttask.h"
#include "game/task/coursetask.h"
#include "game/level/levelinfo.h"
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
void drawLvlEntry();

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
        drawLvlEntry();
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
        ImGui::Checkbox("Location Viewer", &TsuruSaveMgr::sSaveData.locationViewerEnabled); ImGui::SameLine();
        ImGui::Checkbox("Path Viewer", &TsuruSaveMgr::sSaveData.pathViewerEnabled);

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

static void drawLvlEntry() {
    static int world = 0, lvl = 0, entrance = 0;
    static const char* const worlds[] = { "World 1", "World 2", "World 3", "World 4", "World 5", "World 6", "World 7", "World 8", "World 9" };
    static const char* const lvls[] = { "Level 1", "Level 2", "Level 3", "Level 4", "Level 5", "Level 6", "Level 7", "Level 8", "Level 9", "Tower 1", "Tower 2", "Castle 1", "Castle 2", "Ghost House", "Airship", "Secret" };
    static const char* const entrances[] = { "Entrance 0", "Entrance 1", "Entrance 2", "Entrance 3", "Entrance 4", "Entrance 5", "Entrance 6", "Entrance 7", "Entrance 8", "Entrance 9", "Entrance 10", "Entrance 11", "Entrance 12", "Entrance 13", "Entrance 14", "Entrance 15", "Entrance 16", "Entrance 17", "Entrance 18", "Entrance 19", "Entrance 20", "Entrance 21", "Entrance 22", "Entrance 23", "Entrance 24", "Entrance 25", "Entrance 26", "Entrance 27", "Entrance 28", "Entrance 29", "Entrance 30", "Entrance 31", "Entrance 32", "Entrance 33", "Entrance 34", "Entrance 35", "Entrance 36", "Entrance 37", "Entrance 38", "Entrance 39", "Entrance 40", "Entrance 41", "Entrance 42", "Entrance 43", "Entrance 44", "Entrance 45", "Entrance 46", "Entrance 47", "Entrance 48", "Entrance 49", "Entrance 50", "Entrance 51", "Entrance 52", "Entrance 53", "Entrance 54", "Entrance 55", "Entrance 56", "Entrance 57", "Entrance 58", "Entrance 59", "Entrance 60", "Entrance 61", "Entrance 62", "Entrance 63", "Entrance 64", "Entrance 65", "Entrance 66", "Entrance 67", "Entrance 68", "Entrance 69", "Entrance 70", "Entrance 71", "Entrance 72", "Entrance 73", "Entrance 74", "Entrance 75", "Entrance 76", "Entrance 77", "Entrance 78", "Entrance 79", "Entrance 80", "Entrance 81", "Entrance 82", "Entrance 83", "Entrance 84", "Entrance 85", "Entrance 86", "Entrance 87", "Entrance 88", "Entrance 89", "Entrance 90", "Entrance 91", "Entrance 92", "Entrance 93", "Entrance 94", "Entrance 95", "Entrance 96", "Entrance 97", "Entrance 98", "Entrance 99", "Entrance 100", "Entrance 101", "Entrance 102", "Entrance 103", "Entrance 104", "Entrance 105", "Entrance 106", "Entrance 107", "Entrance 108", "Entrance 109", "Entrance 110", "Entrance 111", "Entrance 112", "Entrance 113", "Entrance 114", "Entrance 115", "Entrance 116", "Entrance 117", "Entrance 118", "Entrance 119", "Entrance 120", "Entrance 121", "Entrance 122", "Entrance 123", "Entrance 124", "Entrance 125", "Entrance 126", "Entrance 127", "Entrance 128", "Entrance 129", "Entrance 130", "Entrance 131", "Entrance 132", "Entrance 133", "Entrance 134", "Entrance 135", "Entrance 136", "Entrance 137", "Entrance 138", "Entrance 139", "Entrance 140", "Entrance 141", "Entrance 142", "Entrance 143", "Entrance 144", "Entrance 145", "Entrance 146", "Entrance 147", "Entrance 148", "Entrance 149", "Entrance 150", "Entrance 151", "Entrance 152", "Entrance 153", "Entrance 154", "Entrance 155", "Entrance 156", "Entrance 157", "Entrance 158", "Entrance 159", "Entrance 160", "Entrance 161", "Entrance 162", "Entrance 163", "Entrance 164", "Entrance 165", "Entrance 166", "Entrance 167", "Entrance 168", "Entrance 169", "Entrance 170", "Entrance 171", "Entrance 172", "Entrance 173", "Entrance 174", "Entrance 175", "Entrance 176", "Entrance 177", "Entrance 178", "Entrance 179", "Entrance 180", "Entrance 181", "Entrance 182", "Entrance 183", "Entrance 184", "Entrance 185", "Entrance 186", "Entrance 187", "Entrance 188", "Entrance 189", "Entrance 190", "Entrance 191", "Entrance 192", "Entrance 193", "Entrance 194", "Entrance 195", "Entrance 196", "Entrance 197", "Entrance 198", "Entrance 199", "Entrance 200", "Entrance 201", "Entrance 202", "Entrance 203", "Entrance 204", "Entrance 205", "Entrance 206", "Entrance 207", "Entrance 208", "Entrance 209", "Entrance 210", "Entrance 211", "Entrance 212", "Entrance 213", "Entrance 214", "Entrance 215", "Entrance 216", "Entrance 217", "Entrance 218", "Entrance 219", "Entrance 220", "Entrance 221", "Entrance 222", "Entrance 223", "Entrance 224", "Entrance 225", "Entrance 226", "Entrance 227", "Entrance 228", "Entrance 229", "Entrance 230", "Entrance 231", "Entrance 232", "Entrance 233", "Entrance 234", "Entrance 235", "Entrance 236", "Entrance 237", "Entrance 238", "Entrance 239", "Entrance 240", "Entrance 241", "Entrance 242", "Entrance 243", "Entrance 244", "Entrance 245", "Entrance 246", "Entrance 247", "Entrance 248", "Entrance 249", "Entrance 250", "Entrance 251", "Entrance 252", "Entrance 253", "Entrance 254", "Entrance 255" };

    ImGui::SetNextWindowPos(ImVec2(14.0f, 74.0f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(216.0f, 120.0f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Lvl Entry")) {
        ImGui::Combo("World", &world, worlds, sizeof(worlds) / sizeof(worlds[0]));
        ImGui::Combo("Level", &lvl, lvls, sizeof(lvls) / sizeof(lvls[0]));
        ImGui::Combo("Entrance", &entrance, entrances, sizeof(entrances) / sizeof(entrances[0]));

        sead::TaskBase* currentTask = nullptr;

        if (CourseSelectTask::instance()) {
            currentTask = CourseSelectTask::instance();
        } else if (CourseTask::instance()) {
            currentTask = CourseTask::instance();
        }

        if (ImGui::Button("Play")) {
            int actualLevel = lvl;
            bool valid = true;

            switch (lvl) {
                case 9: // Tower 1
                    actualLevel = 20;
                    break;
                case 10: // Tower 2
                    actualLevel = 21;
                    
                    if (world != 5) {
                        PRINT("Invalid level entered!");
                        valid = false;
                    }
                    break;
                case 11: // Castle 1
                    if (world == 7) {
                        actualLevel = 41;
                    } else {
                        actualLevel = 22;
                    }
                    break;
                case 12: // Castle 2
                    if (world == 7) {
                        actualLevel = 42;
                    } else {
                        PRINT("Invalid level entered!");
                        valid = false;
                    }
                    break;
                case 13: // Ghost House
                    if (world == 2 || world == 3 || world == 4 || world == 6) {
                        actualLevel = 19;
                    } else {
                        PRINT("Invalid level entered!");
                        valid = false;
                    }
                    break;
                case 14: // Airship
                    if (world == 4 || world == 6) {
                        actualLevel = 36;
                    } else {
                        PRINT("Invalid level entered!");
                        valid = false;
                    }
                    break;
                case 15: // Secret
                    switch (world) {
                        case 0: actualLevel = 12; break;
                        case 1: actualLevel = 13; break;
                        case 2: actualLevel = 14; break;
                        case 3: actualLevel = 15; break;
                        case 4: actualLevel = 16; break;
                        default: PRINT("Invalid level entered!"); valid = false; break;
                    }
                    break;
            }

            if (valid) {
                if (LevelInfo::instance()) {
                    LevelInfo::instance()->setDestEntrance(entrance);
                }

                if (currentTask) {
                    TaskMgr::instance()->startLevel(currentTask, world, actualLevel);
                } else {
                    PRINT("Cannot enter level from this scene!");
                }
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Restart") && currentTask == CourseTask::instance() && LevelInfo::instance()) {
            TaskMgr::instance()->startLevel(currentTask, LevelInfo::instance()->world, LevelInfo::instance()->level);
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
