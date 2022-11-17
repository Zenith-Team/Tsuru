#pragma once

/**
 * Holds structs and code for dealing with files outputted by Cobra (https://github.com/RoadrunnerWMC/Cobra)
*/

#include "types.h"
#include "game/csscript.h"
#include "sead/filedevice.h"
#include "sead/filedevicemgr.h"
#include "sead/heap.h"
#include "dynlibs/os/functions.h"
#include "game/actor/courseselect/courseselectactor.h"
#include "log.h"

class WMSFile {
public:
    struct Header {
        char magic[3];
        char version;
        char game;
        char gameVariant[3];
        u32 fileSize;
        u32 numScripts;
    };

    WMSFile(sead::Heap* heap) {
        sead::FileHandle handle;
        sead::FileDevice* device = sead::FileDeviceMgr::instance()->tryOpen(&handle, "course_select/scripts.wmsc", sead::FileDevice::FileOpenFlag_ReadOnly, 0);

        const s32 align = sead::FileDevice::sBufferMinAlignment;

        if (!handle.device) {
            PRINT(LogColor::Red, "scripts.wmsc not found.");
            return;
        }

        u8* headerBuffer = (u8*)heap->tryAlloc(sizeof(Header), align);

        u32 bytesRead = handle.read(reinterpret_cast<u8*>(headerBuffer), sizeof(Header));
        OSBlockMove(&this->header, headerBuffer, sizeof(Header), false);

        if (bytesRead != sizeof(Header)) {
            PRINT(LogColor::Red, "scripts.wmsc header read size mismatch, read size: ", fmt::hex, bytesRead, ", expected size: ", fmt::hex, sizeof(Header));
            return;
        }

        u32* scriptIDBuffer = (u32*)heap->tryAlloc(sizeof(u32) * this->header.numScripts, align);
        CSScript* scriptBuffer = (CSScript*)heap->tryAlloc(sizeof(CSScript) * this->header.numScripts, align);

        bytesRead = handle.read(reinterpret_cast<u8*>(scriptIDBuffer), sizeof(u32) * this->header.numScripts);

        if (bytesRead != sizeof(u32) * this->header.numScripts) {
            PRINT(LogColor::Red, "scripts.wmsc script ID read size mismatch, read size: ", fmt::hex, bytesRead, ", expected size: ", fmt::hex, sizeof(u32) * this->header.numScripts);
            return;
        }

        bytesRead = handle.read(reinterpret_cast<u8*>(scriptBuffer), sizeof(CSScript) * this->header.numScripts);

        if (bytesRead != sizeof(CSScript) * this->header.numScripts) {
            PRINT(LogColor::Red, "scripts.wmsc script read size mismatch, read size: ", fmt::hex, bytesRead, ", expected size: ", fmt::hex, sizeof(CSScript) * this->header.numScripts);
            return;
        }

        this->scriptIDs = (u32*)heap->tryAlloc(sizeof(u32) * this->header.numScripts, sizeof(u32));
        OSBlockMove(this->scriptIDs, scriptIDBuffer, sizeof(u32) * this->header.numScripts, false);

        this->scripts = (CSScript*)heap->tryAlloc(sizeof(CSScript) * this->header.numScripts, sizeof(CSScript));
        OSBlockMove(this->scripts, scriptBuffer, sizeof(CSScript) * this->header.numScripts, false);

        u32 dataSize = this->header.fileSize - sizeof(Header) - (sizeof(u32) * this->header.numScripts) - (sizeof(CSScript) * this->header.numScripts);

        u8* scriptDataBuffer = (u8*)heap->tryAlloc(dataSize, align);

        bytesRead = handle.read(reinterpret_cast<u8*>(scriptDataBuffer), dataSize);

        if (bytesRead != dataSize) {
            PRINT(LogColor::Red, "scripts.wmsc script data read size mismatch, read size: ", fmt::hex, bytesRead, ", expected size: ", fmt::hex, dataSize);
            return;
        }

        this->scriptsData = (CSScriptCommand*)heap->tryAlloc(dataSize, sizeof(CSScriptCommand));
        OSBlockMove(this->scriptsData, scriptDataBuffer, dataSize, false);

        u32 fileOffsetToScriptsData = sizeof(Header) + (sizeof(u32) * this->header.numScripts) + (sizeof(CSScript) * this->header.numScripts);
        for (int i = 0; i < this->header.numScripts; i++) {
            u32* ptrToScriptStart = (u32*)(&this->scripts[i].scriptStart);
            *ptrToScriptStart -= fileOffsetToScriptsData;
            *ptrToScriptStart += (u32)(this->scriptsData);
        }

        heap->free(headerBuffer);
        heap->free(scriptIDBuffer);
        heap->free(scriptBuffer);
        heap->free(scriptDataBuffer);
    }

    Header header;
    u32* scriptIDs;
    CSScript* scripts;
    CSScriptCommand* scriptsData;
};

class CSScriptLoader : public CourseSelectActor {
public:
    CSScriptLoader(const ActorBuildInfo* buildInfo);
    virtual ~CSScriptLoader() { }

    static Actor* build(const ActorBuildInfo* buildInfo);

    u32 onCreate() override;
    u32 onExecute() override { return 1; }
    u32 onDraw() override { return 1; }

    static CSScriptLoader* instance;

    WMSFile* wmscFile;
};
