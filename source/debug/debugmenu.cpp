#include "game/actor/actormgr.h"
#include "game/actor/stage/player.h"
#include "game/actor/courseselect/courseselectactorbase.h"
#include "sead/heapmgr.h"
#include "sead/taskmgr.h"
#include "sead/controllermgr.h"
#include "sead/scopedlock.h"
#include "sead/threadmgr.h"
#include "sead/sharcarchiveres.h"
#include "tsuru/save/managers/tsurusavemgr.h"
#include "game/wrappedcontroller.h"
#include "game/task/taskmgr.h"
#include "game/task/courseselecttask.h"
#include "game/task/coursetask.h"
#include "game/level/levelinfo.h"
#include "game/level/levelcamera.h"
#include "game/graphics/tiletexmgr.h"
#include "game/resource/resmgr.h"
#include "game/sound/sndaudiomgr.h"
#include "game/sound/sndbgmmgr.h"
#include "agl/texturesampler.h"
#include "agl/lyr/renderer.h"
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

void drawHeapMgrImGui();
void drawThreadMgrImGui();
void drawMethodTreeMgrImGui(sead::DualScreenMethodTreeMgr* mgr);
void drawTaskMgrImGui(sead::TaskMgr* mgr);
void drawResMgrImGui();
void drawSndAudioMgrImGui();
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

        if (counter == 60 * 2) {
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
        // NSMBU sead::ThreadMgr doesn't have a mutex lock to the list... maybe this is bad
        drawThreadMgrImGui();
        drawMethodTreeMgrImGui((sead::DualScreenMethodTreeMgr*)sead::ControllerMgr::instance()->getMethodTreeMgr());
        drawTaskMgrImGui(sead::ControllerMgr::instance()->taskMgr);

        if (ResMgr::instance()) {
            drawResMgrImGui();
        }

        if (SndAudioMgr::instance()) {
            drawSndAudioMgrImGui();
        }

        if (ActorMgr::instance()) {
            drawActorMgrImGui();
        }
    }
    ImGui::End();
}

static void drawHacks() {
    ImGui::SetNextWindowPos(ImVec2(16.0f, 197.0f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(176.0f, 140.0f));
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
/*         if (TileTexMgr::instance()) {
            //agl::TextureData& textureData = TileTexMgr::instance()->textureAnimations[0];
            agl::TextureData& textureData = agl::lyr::Renderer::instance()->renderBuffers[0]->targetColors[0]->textureData;
            textureData.invalidateGPUCache();

            static agl::TextureSampler textureSampler;
            textureSampler.applyTextureData(textureData);
            textureSampler.setup(); // calls initRegs_() if needed

            static ImGui_ImplGX2_Texture imGuiTexture;
            imGuiTexture.Texture = &textureSampler.texture;
            imGuiTexture.Sampler = &textureSampler.sampler;

            static MemoryEditor memEditor;
            memEditor.DrawWindow("Memory Editor", textureSampler.textureData.getImagePtr(), textureSampler.textureData.getImageByteSize());

            ImGui::Text("ptr: %p, size: 0x%08X", textureSampler.textureData.getImagePtr(), textureSampler.textureData.getImageByteSize());
            ImGui::Image(&imGuiTexture, ImVec2(textureSampler.textureData.getWidth() / 2, textureSampler.textureData.getHeight() / 2));
        } */

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

    ImGui::SetNextWindowPos(ImVec2(14.0f, 50.0f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(216.0f, 140.0f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Lvl Entry")) {
        ImGui::Combo("World", &world, worlds, sizeof(worlds) / sizeof(worlds[0]));
        ImGui::Combo("Level", &lvl, lvls, sizeof(lvls) / sizeof(lvls[0]));
        ImGui::InputInt("Entrance", &entrance, 1, 10);

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

        for (u32 i = 0; i < sead::HeapMgr::sIndependentHeaps.ptrNum; i++) {
            drawHeapImGui((sead::Heap*)sead::HeapMgr::sIndependentHeaps.ptrs[i]);
        }
    }
}

// NSMBU sead::ThreadMgr doesn't have a mutex lock to the list... maybe this is bad
static void drawThreadImGui(const sead::Thread* thread) {
    //FormatFixedSafeString<64> buf("%s###%d", thread->getName().cstr(), thread);

    char buf[128] = { 0 };
    __os_snprintf(buf, 128, "%s###%d", thread->getName().cstr(), thread);

    if (ImGui::TreeNode(buf)) {
        const char* blockType = thread->blockType == sead::MessageQueue::BlockType_Block ? "Block" : "NoBlock";
        const char* currentHeap = thread->currentHeap != nullptr ? thread->currentHeap->getName().cstr() : "nullptr";
        static const char* const states[] = {
            "Initialized", "Running", "Quitting", "Terminated", "Released"
        };

        ImGui::Text("Priority: %d", thread->priority);
        ImGui::Text("BlockType: %s", blockType);
        ImGui::Text("QuitMsg: 0x%X", thread->quitMsg);
        ImGui::Text("StackSize: 0x%X", thread->stackSize);
        ImGui::Text("CurrentHeap: %s", currentHeap);
        ImGui::Text("Id: 0x%X", thread->id);
        ImGui::Text("State: %s", states[thread->state]);
        ImGui::Text("StackTop: 0x%X", thread->stackTop);

        ImGui::TreePop();
    }
}

static void drawThreadMgrImGui() {
    // NSMBU sead::ThreadMgr doesn't have a mutex lock to the list... maybe this is bad
    //sead::ScopedLock<sead::CriticalSection> lock(sead::ThreadMgr::instance()->listCriticalSection);

    if (ImGui::CollapsingHeader("sead::ThreadMgr")) {
        drawThreadImGui(sead::ThreadMgr::instance()->getMainThread());

        for (sead::Thread::List::iterator it = sead::ThreadMgr::instance()->list.begin(); it != sead::ThreadMgr::instance()->list.end(); ++it) {
            drawThreadImGui(*it);
        }
    }
}

static bool sShowPauseFlagMethodTree = false;

static void drawMethodTreeImGui(sead::MethodTreeNode* m) {
    //FormatFixedSafeString<64> buf("%s###%d", m->getName().cstr(), m);

    char buf[128] = { 0 };
    __os_snprintf(buf, 128, "%s###%d", m->getName().cstr(), m);

    if (ImGui::TreeNode(buf)) {
        if (sShowPauseFlagMethodTree) {
            sead::BitFlag32 flag = m->pauseFlag;
            bool pauseSelf = flag.isOn(sead::MethodTreeNode::Pause_Self);
            bool pauseChild = flag.isOn(sead::MethodTreeNode::Pause_Child);
            bool pauseBoth = flag.isOn(sead::MethodTreeNode::Pause_Both);

            ImGui::SameLine();
            if (ImGui::SmallButton(pauseSelf ? "PauseSelf On" : "PauseSelf Off")) {
                flag.toggle(sead::MethodTreeNode::Pause_Self);
                m->setPauseFlag((sead::MethodTreeNode::PauseFlag)flag.getDirect());
            }

            ImGui::SameLine();
            if (ImGui::SmallButton(pauseChild ? "PauseChild On" : "PauseChild Off")) {
                flag.toggle(sead::MethodTreeNode::Pause_Child);
                m->setPauseFlag((sead::MethodTreeNode::PauseFlag)flag.getDirect());
            }
        }

        sead::TTreeNode<sead::MethodTreeNode*>* node = (sead::TTreeNode<sead::MethodTreeNode*>*)m->child;

        while (node) {
            drawMethodTreeImGui(node->data);
            node = (sead::TTreeNode<sead::MethodTreeNode*>*)node->data->next;
        }

        ImGui::TreePop();
    }
}

static void drawMethodTreeMgrImGui(sead::DualScreenMethodTreeMgr* mgr) {
    sead::ScopedLock<sead::CriticalSection> lock(mgr->criticalSection);

    if (ImGui::CollapsingHeader("sead::MethodTreeMgr")) {
        ImGui::Checkbox("Show PauseFlags", &sShowPauseFlagMethodTree);

        ImGui::Separator();

        drawMethodTreeImGui(&mgr->rootCalcNode);
        drawMethodTreeImGui(&mgr->topRootDrawNode);
        drawMethodTreeImGui(&mgr->btmRootDrawNode);
    }
}

static void drawTaskImGui(const sead::TaskBase* task) {
    //FormatFixedSafeString<64> buf("%s###%d", task->getName().cstr(), task);

    char buf[128] = { 0 };
    __os_snprintf(buf, 128, "%s###%d", task->getName().cstr(), task);

    if (ImGui::TreeNode(buf)) {
        ImGui::SameLine();
        if (ImGui::SmallButton("destroy")) {
            //task->requestDestroyTask();
            //task->destroyTaskSync();
            ImGui::TreePop();
            return;
        }

        static const char* const states[] = {
            "Created", "Prepare", "PrepareDone", "Sleep", "Running", "Dying", "Destroyable", "Dead"
        };

        sead::BitFlag32 flag = task->internalFlag;
        bool fading = flag.isOn(sead::TaskBase::Flag_Fading);
        bool unk1 = flag.isOn(sead::TaskBase::Flag_Unk1);
        bool unk2 = flag.isOn(sead::TaskBase::Flag_Unk2);

        const char* tag = task->tag == sead::TaskBase::Tag_System ? "System" : "App";

        ImGui::Text("Flags: 0x%08X", flag.getDirect());
        ImGui::BulletText(" Fading: %s", fading ? "true" : "false");
        ImGui::BulletText(" Unk1: %s", unk1 ? "true" : "false");
        ImGui::BulletText(" Unk2: %s", unk2 ? "true" : "false");
        ImGui::Text("State: %s", states[task->state]);
        ImGui::Text("Tag: %s", tag);

        ImGui::TreePop();
    }
}

static void drawTaskListImGui(const sead::TaskBase::List& list, const char* name) {
    if (ImGui::TreeNodeEx(name, ImGuiTreeNodeFlags_NoTreePushOnOpen)) {
        ImGui::TreePush(name);

        for (sead::TaskBase::List::iterator it = list.begin(); it != list.end(); ++it)
            drawTaskImGui(*it);

        ImGui::TreePop();
    }
}

static void drawTaskMgrImGui(sead::TaskMgr* mgr) {
    //sead::ScopedLock<sead::CriticalSection> lock(mgr->criticalSection); // causes game to freeze when entering level

    if (ImGui::CollapsingHeader("sead::TaskMgr")) {
        drawTaskListImGui(mgr->prepareList, "PrepareList");
        drawTaskListImGui(mgr->prepareDoneList, "PrepareDoneList");
        drawTaskListImGui(mgr->activeList, "ActiveList");
        drawTaskListImGui(mgr->staticList, "StaticList");
        drawTaskListImGui(mgr->dyingList, "DyingList");
        drawTaskListImGui(mgr->destroyableList, "DestroyableList");
    }
}

static void drawSharcArchiveResImGui(sead::SharcArchiveRes* archiveRes) {
    sead::Buffer<const sead::SharcArchiveRes::FATEntry>& entrys = archiveRes->fatEntrys;

    sead::FixedSafeString<128> fileName;

    for (u32 i = 0; i < entrys.size; i++) {
        archiveRes->getFATEntryName(&fileName, entrys[i]);

        ImGui::Text(fileName.cstr());
    }
}

static void resCallback(const sead::SafeString& key, ResMgr::ResHolder*& value) {
    if (ImGui::TreeNode(key.cstr())) {
        drawSharcArchiveResImGui(value->archiveRes);

        ImGui::TreePop();
    }
}

static void drawResMgrImGui() {
    if (ImGui::CollapsingHeader("ResMgr")) {
        ImGui::Text("Resource Num: %u", ResMgr::instance()->resHolderTreeMap.getSize());

        ResMgr::instance()->resHolderTreeMap.forEach(&resCallback);

        if (ResMgr::instance()->levelArchiveRes) {
            ImGui::Separator();

            if (ImGui::TreeNode("LevelArchiveRes")) {
                drawSharcArchiveResImGui(ResMgr::instance()->levelArchiveRes);

                ImGui::TreePop();
            }
        }
    }
}

static void drawSoundHandleImGui(nw::snd::SoundHandle* handle, u32 i) {
    char buf[64] = { 0 };
    __os_snprintf(buf, 64, "SoundHandle%i: %s", i + 1, handle->IsAttachedSound() ? "Attached" : "Detached");

    if (ImGui::TreeNode(buf)) {
        if (ImGui::Button("Stop"))
            handle->Stop(0);

        nw::snd::SequenceSoundHandle sequenceHandle(handle);
        if (sequenceHandle.IsAttachedSound()) {
            static int var = 0;

            static const char* const vars[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

            ImGui::Combo("Var0", &var, vars, sizeof(vars) / sizeof(vars[0]));
            if (ImGui::Button("Set Var0"))
                sequenceHandle.WriteVariable(0, var);
        }

        ImGui::TreePop();
    }
}

static void drawSndAudioMgrImGui() {
    if (ImGui::CollapsingHeader("SndAudioMgr")) {
        SndAudioMgr* audioMgr = SndAudioMgr::instance();

        nw::snd::SoundHandle* handles = &audioMgr->soundHandle1;

        for (u32 i = 0; i < 10; i++) {
            drawSoundHandleImGui(&handles[i], i);
        }

        ImGui::Text("Beat: %i", audioMgr->currentBeat);
        ImGui::Text("Tick: %i", SndBgmMgr::instance()->currentTick);
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

        Player* player = sead::DynamicCast<Player>(actor);
        if (player) {
            static int powerup = 0;

            static const char* const powerups[] = { "Small", "Big", "Fire", "Mini", "Propeller", "Penguin", "Ice", "Acorn", "PAcorn", "Hammer" };

            ImGui::Combo("Powerup", &powerup, powerups, sizeof(powerups) / sizeof(powerups[0]));
            
            if (ImGui::Button("Set Powerup"))
                player->givePowerup((PlayerBase::PowerupState::__type__)powerup);
        }

        CourseSelectActorBase* csActor = sead::DynamicCast<CourseSelectActorBase>(actor);
        if (csActor) {
            ImGui::DragFloat3("Position", &csActor->position.x);
            ImGui::DragFloat3("Scale", &csActor->scale.x);
            ImGui::DragInt("Rotation", (int*)&csActor->rotation);
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
