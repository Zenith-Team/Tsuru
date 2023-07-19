#include "imgui/imgui.h"
#include "game/actor/actormgr.h"
#include "sead/heapmgr.h"
#include "sead/scopedlock.h"

extern "C" u32 expHeapVtable[];
extern "C" u32 frameHeapVtable[];
extern "C" u32 unitHeapVtable[];
extern "C" u32 separateHeapVtable[];

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

    if (ImGui::TreeNode(buf))
    {
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

        if (heap->children.count > 0)
        {
            ImGui::Text("Children: %d", heap->children.count);

            for (sead::OffsetList<sead::Heap>::iterator it = heap->children.begin(); it != heap->children.end(); ++it)
            {
                drawHeapImGui(&*it);
            }
        }
        else
        {
            ImGui::Text("Children: 0");
        }

        ImGui::TreePop();
    }
}

static void drawHeapMgrImGui() {
    sead::ScopedLock<sead::CriticalSection> lock(sead::HeapMgr::sHeapTreeLockCS);

    if (ImGui::CollapsingHeader("sead::HeapMgr"))
    {
        for (u32 i = 0; i < sead::HeapMgr::sRootHeaps.ptrNum; i++)
        {
            drawHeapImGui((sead::Heap*)sead::HeapMgr::sRootHeaps.ptrs[i]);
        }
    }
}

static void drawProfileImGui(const Profile* profile) {
    //FormatFixedSafeString<64> buf("profile: %d###%d", profile->id, profile);

    char buf[64] = { 0 };
    __os_snprintf(buf, 64, "Profile: %d###%d", profile->id, profile);

    if (ImGui::TreeNode(buf))
    {
        ImGui::Text("BuildFunc: 0x%X", profile->buildFunc);
        ImGui::Text("Priority: %i", profile->getPriority(profile->id));

        ImGui::TreePop();
    }
}

static void drawActorImGui(Actor* actor) {
    //FormatFixedSafeString<128> buf("0x%08X###%d", actor->id, actor);

    char buf[128] = { 0 };
    __os_snprintf(buf, 128, "0x%08X###%d", actor->id, actor);

    if (ImGui::TreeNode(buf))
    {
        drawHeapImGui(actor->heap);
        drawProfileImGui(actor->profile);

        ImGui::Text("WasNotDeferred: %s", actor->wasNotDeferred ? "True" : "False");
        ImGui::Text("IsCreated: %s", actor->isCreated ? "True" : "False");
        ImGui::Text("IsDeleted: %s", actor->isDeleted ? "True" : "False");

        ImGui::SameLine();
        if (ImGui::SmallButton("delete"))
            actor->isDeleted = true;

        ImGui::Text("Settings1: 0x%08X", actor->settings1);
        ImGui::Text("Settings2: 0x%08X", actor->settings2);

        ImGui::Text("Children Count: %d", actor->childList.count);

        if (actor->parent)
            ImGui::Text("Parent: 0x%08X", actor->parent->id);
        else
            ImGui::Text("Parent: nullptr");

        StageActor* stageActor = sead::DynamicCast<StageActor>(actor);
        if (stageActor)
        {
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
    if (ImGui::CollapsingHeader("ActorMgr"))
    {
        ActorMgr* actorMgr = ActorMgr::instance();

        ImGui::Text("Actor Count: %u", actorMgr->activeActors.count + actorMgr->actorsToDelete.count);

        ActorBuffer* actors = &actorMgr->actors;
        for (u32 i = 0; i < actors->start.size; i++)
        {
            Actor* actor = actors->start[i];
            if (actor)
                drawActorImGui(actor);
        }
    }
}

static void drawMgrsImGui() {
    ImGui::ShowDemoWindow();

    if (ImGui::Begin("Mgr's Info"))
    {
        drawHeapMgrImGui();

        if (ActorMgr::instance())
            drawActorMgrImGui();
    }
    ImGui::End();
}

void tsuruDebugMenu() {
    drawMgrsImGui();
}
