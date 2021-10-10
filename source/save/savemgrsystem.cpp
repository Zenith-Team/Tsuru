#include <tsuru/save/savemgrsystem.h>
#include <tsuru/save/customsavemgr.h>

SEAD_SINGLETON_DISPOSER_IMPL(SaveMgrSystem)

SaveMgrSystem::SaveMgrSystem()
    : customManagers()
{ }

void SaveMgrSystem::globalInit() {
    SaveMgrSystem::createInstance(nullptr)->initAllManagers();
}

void SaveMgrSystem::globalSave() {
    SaveMgrSystem::instance()->saveAllManagers();
}

void SaveMgrSystem::initAllManagers() {
    for (u32 i = 0; i < this->customManagers.size; i++) {
        if (this->customManagers.buffer[i]) {
            this->customManagers.buffer[i]->init();
        }
    }
}

void SaveMgrSystem::saveAllManagers() {
    for (u32 i = 0; i < this->customManagers.size; i++) {
        if (this->customManagers.buffer[i]) {
            this->customManagers.buffer[i]->save();
        }
    }
}

void SaveMgrSystem::addToList(CustomSaveMgr* manager) {
    this->customManagers.buffer[this->customManagers.size++] = manager;
}
