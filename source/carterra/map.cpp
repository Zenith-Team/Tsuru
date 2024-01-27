#include "tsuru/carterra/map.h"
#include "tsuru/carterra/scene.h"
#include "dynlibs/os/functions.h"
#include "game/resource/util.h"
#include "game/savemgr.h"
#include "sead/heapmgr.h"
#include "sead/filedevice.h"
#include "sead/filedevicemgr.h"
#include "tsuru/save/managers/carterrasavemgr.h"
#include "log.h"

namespace crt {
    REGISTER_PROFILE(Map, ProfileID::CarterraMap);
}

// TODO: Reset these when the save is loaded
static bool pathsUnlockedInited = false;
bool crt::Map::pathsUnlocked[512] = {false};

static void findUnlockCriteriaSize(u8* unlockCriteria, u32& idx) {
	u8 controlByte = unlockCriteria[idx++];
	u8 conditionType = controlByte >> 6;

	if (conditionType == 0) {
		u8 subConditionType = (controlByte & 0x3F);
		if (subConditionType < 4) {
			idx += 2;
        }
	} else if (conditionType == 1) {
		++idx;
	} else if (conditionType == 2 || conditionType == 3) {
		u8 termCount = (controlByte & 0x3F) + 1;
		for (int i = 0; i < termCount; i++) {
			findUnlockCriteriaSize(unlockCriteria, idx);
		}
	}
}

static bool evaluateUnlockCriteria(u8*& in) {
	u8 controlByte = *(in++);
	u8 conditionType = (controlByte >> 6);

	if (conditionType == 0) {
		u8 subConditionType = controlByte & 0x3F;
		switch (subConditionType) {
			case 15:
				return true;
			default:
				return false;
		}
	} else if (conditionType == 1) {
		bool isSecret = (controlByte & 0x10);
		u8 worldNumber = controlByte & 0xF;
		u8 levelNumber = *(in++);

		u32 conds = CarterraSaveMgr::sSaveData.saveSlots[SaveMgr::instance()->saveData->header.lastSessionSaveSlot].levelCompletions[worldNumber][levelNumber];

		if (isSecret)
			return (conds & CarterraSaveMgr::CarterraSaveData::LevelCompletion::SecretExit) != 0;
		else
			return (conds & CarterraSaveMgr::CarterraSaveData::LevelCompletion::NormalExit) != 0;
	}

	// Type: 2 = AND, 3 = OR
	bool isAnd = (conditionType == 2);
	bool isOr = (conditionType == 3);

	bool value = isOr ? false : true;

	u8 termCount = (controlByte & 0x3F) + 1;

	for (int i = 0; i < termCount; i++) {
		bool what = evaluateUnlockCriteria(in);

		if (isOr)
			value |= what;
		else if (isAnd)
			value &= what;
	}

	return value;
}

crt::MapData::MapData(u8* data) {
	MapData::Header* header = reinterpret_cast<MapData::Header*>(data);
	MapData::WorldInfo* worldInfo = reinterpret_cast<MapData::WorldInfo*>(data + sizeof(MapData::Header));
	
	this->header.magic = (header->magic);
	this->header.version = (header->version);
	this->header.mapID = (header->mapID);

	this->worldInfo.worldID = (worldInfo->worldID);
	memcpy(this->worldInfo.name, worldInfo->name, 32);
	this->worldInfo.accentColor = (worldInfo->accentColor);

	u32 nodeCount = (*reinterpret_cast<u32*>(data + sizeof(MapData::Header) + sizeof(MapData::WorldInfo)));
	this->nodes = new MapData::Node[nodeCount];
	for (u32 i = 0; i < nodeCount; i++) {
		MapData::Node* node = reinterpret_cast<MapData::Node*>(data + sizeof(MapData::Header) + sizeof(MapData::WorldInfo) + sizeof(u32) + (sizeof(MapData::Node) * i));

		this->nodes[i].type = (node->type);
		memcpy(this->nodes[i].boneName, node->boneName, 32);

		switch (this->nodes[i].type) {
			case MapData::Node::Type::Normal: {
				break;
			}

			case MapData::Node::Type::Passthrough: {
				break;
			}

			case MapData::Node::Type::Level: {
				this->nodes[i].level.levelID = (node->level.levelID);
				this->nodes[i].level.unlocksMapID = (node->level.unlocksMapID);

				break;
			}
		}
	}

	u32 pathCount = (*reinterpret_cast<u32*>(data + sizeof(MapData::Header) + sizeof(MapData::WorldInfo) + sizeof(u32) + (sizeof(MapData::Node) * nodeCount)));
	this->paths = new MapData::Path[pathCount];
	for (u32 i = 0; i < pathCount; i++) {
		MapData::Path* path = reinterpret_cast<MapData::Path*>(data + sizeof(MapData::Header) + sizeof(MapData::WorldInfo) + sizeof(u32) + (sizeof(MapData::Node) * nodeCount) + sizeof(u32) + (sizeof(MapData::Path) * i));

		this->paths[i].startingNodeIndex = (path->startingNodeIndex);
		this->paths[i].endingNodeIndex = (path->endingNodeIndex);
		this->paths[i].speed = (path->speed);
		this->paths[i].animation = (path->animation);

		u32 unlockCriteriaOffset = (u32)(path->unlockCriteria);
		u8* unlockCriteria = data + unlockCriteriaOffset;

		u32 ucSize = 0;
		findUnlockCriteriaSize(unlockCriteria, ucSize);

		this->paths[i].unlockCriteria = new u8[ucSize];
		memcpy(this->paths[i].unlockCriteria, unlockCriteria, ucSize);
	}
}

crt::Map::Map(const ActorBuildInfo* buildInfo)
    : crt::MapActor(buildInfo)
    , model(nullptr)
    , bones(nullptr)
    , sceneHeap((sead::Heap*)buildInfo->rotation) // Reuse the rotation field to pass the scene heap
	, data(nullptr)
	, courseModels(nullptr)
	, courseModelCount(0)
{
    sead::HeapMgr::instance()->setCurrentHeap(this->sceneHeap);

    char name[32] = {0};
    char modelPath[32] = {0};
    char dataPath[32] = {0};
    __os_snprintf(name, 32, "CS_W%d", this->settings1);
    __os_snprintf(modelPath, 64, "course_select/%s.szs", name);
    __os_snprintf(dataPath, 64, "course_select/%s.a2ls", name);

    loadResource(name, modelPath);
	loadResource("cobCourse", "actor/cobCourse.szs");

    sead::FileHandle handle;
    sead::FileDeviceMgr::instance()->tryOpen(&handle, dataPath, sead::FileDevice::FileOpenFlag_ReadOnly, 0);

    u32 fileSize = handle.getFileSize();

    u8* fileData = (u8*)this->sceneHeap->tryAlloc(fileSize, sead::FileDevice::sBufferMinAlignment);

    if (fileData == nullptr) {
        PRINT("Failed to allocate memory for map: ", dataPath);
        return;
    }

    u32 bytesRead = handle.read(fileData, fileSize);

    this->data = new MapData(fileData);

    delete[] fileData;

	if (pathsUnlockedInited == false) {
		PRINT("Initing pathsUnlocked");

		for (u32 i = 0; i < this->data->pathCount; i++) {
        	Map::pathsUnlocked[i] = evaluateUnlockCriteria(this->data->paths[i].unlockCriteria);
		}

		pathsUnlockedInited = true;
	}

	u32 courseNodeCount = 0;
	for (u32 i = 0; i < this->data->nodeCount; i++) {
		if (this->data->nodes[i].type == MapData::Node::Type::Level) {
			courseNodeCount++;
		}
	}

	this->courseModels = new ModelWrapper*[courseNodeCount];
	for (u32 i = 0; i < courseNodeCount; i++) {
		this->courseModels[i] = ModelWrapper::create("cobCourse", "cobCourse", 0, 0, 2);
		this->courseModels[i]->playColorAnim("cobCourseClear");
		this->courseModels[i]->texSrtAnims[0]->frameCtrl.speed = 0;
	}

	this->courseModelCount = courseNodeCount;
}

u32 crt::Map::onCreate() {
    sead::HeapMgr::instance()->setCurrentHeap(this->sceneHeap);

    char name[32] = {0};
    char terrainModelName[32] = {0};
	char synchroModelName[32] = {0};

    __os_snprintf(name, 32, "CS_W%d", this->settings1);
    __os_snprintf(terrainModelName, 32, "CS_W%d_World", this->settings1);
	__os_snprintf(synchroModelName, 32, "CS_W%d_Synchro", this->settings1);

    this->model = ModelWrapper::create(name, terrainModelName);
    this->bones = ModelWrapper::create(name, name);
	this->synchro = ModelWrapper::create(name, synchroModelName, 1);

	this->synchro->playSklAnim(synchroModelName);

    Mtx34 mtx;
    mtx.makeRTIdx(0, this->position);

    this->bones->setMtx(mtx);
    this->bones->setScale(0.1f);
    this->bones->updateModel();

    this->model->setMtx(mtx);
    this->model->setScale(0.1f);
    this->model->updateModel();

	this->synchro->setMtx(mtx);
	this->synchro->setScale(0.1f);

    return 1;
}

u32 crt::Map::onExecute() {
	this->synchro->updateAnimations();
	this->synchro->updateModel();

	Mtx34 mtx;
	for (u32 i = 0, j = 0; i < this->data->nodeCount; i++) {
		if (this->data->nodes[i].type == MapData::Node::Type::Level) {
			CarterraSaveMgr::CarterraSaveData::SaveSlot* slot = &CarterraSaveMgr::sSaveData.saveSlots[SaveMgr::instance()->saveData->header.lastSessionSaveSlot];
			u8 flag = slot->levelCompletions[this->settings1-1][this->data->nodes[i].level.levelID-1];
			bool completed = (flag & CarterraSaveMgr::CarterraSaveData::LevelCompletion::NormalExit) || (flag & CarterraSaveMgr::CarterraSaveData::LevelCompletion::SecretExit);

			if (completed) {
				this->courseModels[j]->playColorAnim("cobCourseClear");
				this->courseModels[j]->texSrtAnims[0]->frameCtrl.speed = 0;
				this->courseModels[j]->texSrtAnims[0]->frameCtrl.currentFrame = 1;
			}

			Vec3f pos = this->getBonePos(this->data->nodes[i].boneName);
			mtx.makeRTIdx(0, pos);
			this->courseModels[j]->setMtx(mtx);
			this->courseModels[j]->setScale(0.1f);
			this->courseModels[j]->updateModel();
			this->courseModels[j]->updateAnimations();

			j++;
		}
	}

	return 1;
}

u32 crt::Map::onDraw() {
    this->model->draw();
	this->synchro->draw();

	for (u32 i = 0; i < this->courseModelCount; i++) {
		this->courseModels[i]->draw();
	}

    return 1;
}

u32 crt::Map::onDelete() {
    delete this->model;
    delete this->bones;
	delete this->synchro;
	delete this->data;
	delete[] this->courseModels;
    
    return 1;
}

Vec3f crt::Map::getBonePos(const sead::SafeString& name) {
    Mtx34 mtx;
    this->bones->model->getBoneWorldMatrix(this->bones->model->searchBoneIndex(name), &mtx);

    return Vec3f(mtx.m[0][3], mtx.m[1][3], mtx.m[2][3]);
}

crt::MapData::Node* crt::Map::getNode(const sead::SafeString& name) {
	for (u32 i = 0; i < this->data->nodeCount; i++) {
		if (strcmp(name.cstr(), this->data->nodes[i].boneName)) {
			return &this->data->nodes[i];
		}
	}

	PRINT("ERROR: Unable to find node: ", name.cstr());

	return nullptr;
}

void crt::Map::checkUnlocks() {
	for (u32 i = 0; i < this->data->pathCount; i++) {
		if (Map::pathsUnlocked[i]) {
			continue;
		}

        Map::pathsUnlocked[i] = evaluateUnlockCriteria(this->data->paths[i].unlockCriteria);
	}

	for (u32 i = 0, j = 0; i < this->data->nodeCount; i++) {
		if (this->data->nodes[i].type == MapData::Node::Type::Level) {
			for (u32 k = 0; k < this->data->pathCount; k++) {
				if (Map::pathsUnlocked[k]) {
					if (this->data->paths[k].startingNodeIndex == i || this->data->paths[k].endingNodeIndex == i) {
						this->courseModels[j]->playColorAnim("cobCourseOpen");
						this->courseModels[j]->texSrtAnims[0]->frameCtrl.speed = 1;
					}
				}
			}

			j++;
		}
	}
}
