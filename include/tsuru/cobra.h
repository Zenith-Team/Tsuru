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
        u32 numScripts;
    };

    WMSFile(sead::Heap* heap) {
        sead::FileHandle handle;
        sead::FileDevice* device = sead::FileDeviceMgr::instance()->tryOpen(&handle, "scripts.wms", sead::FileDevice::FileOpenFlag_ReadOnly, 0);

        const s32 align = sead::FileDevice::sBufferMinAlignment;

        u8* headerBuffer = (u8*)heap->tryAlloc(sizeof(Header), align);

        if (!handle.device) {
            PRINT(LogColor::Red, "scripts.wms not found.");
            return;
        }

        u32 size = 0;
        bool b = device->doGetFileSize_(&size, &handle);
        PRINT(size);
        PRINT(b);

        u32 bytesRead = handle.read(reinterpret_cast<u8*>(headerBuffer), sizeof(Header));
        OSBlockMove(&this->header, headerBuffer, sizeof(Header), false);

        if (bytesRead != sizeof(Header)) {
            PRINT(LogColor::Red, "scripts.wms header read size mismatch, read size: ", fmt::hex, bytesRead, ", expected size: ", fmt::hex, sizeof(Header));
            return;
        }

        u32* scriptIDBuffer = (u32*)heap->tryAlloc(sizeof(u32) * this->header.numScripts, align);
        CSScript* scriptBuffer = (CSScript*)heap->tryAlloc(sizeof(CSScript) * this->header.numScripts, align);

        bytesRead = handle.read(reinterpret_cast<u8*>(scriptIDBuffer), sizeof(u32) * this->header.numScripts);

        if (bytesRead != sizeof(u32) * this->header.numScripts) {
            PRINT(LogColor::Red, "scripts.wms script ID read size mismatch, read size: ", fmt::hex, bytesRead, ", expected size: ", fmt::hex, sizeof(u32) * this->header.numScripts);
            return;
        }

        bytesRead = handle.read(reinterpret_cast<u8*>(scriptBuffer), sizeof(CSScript) * this->header.numScripts);

        if (bytesRead != sizeof(CSScript) * this->header.numScripts) {
            PRINT(LogColor::Red, "scripts.wms script read size mismatch, read size: ", fmt::hex, bytesRead, ", expected size: ", fmt::hex, sizeof(CSScript) * this->header.numScripts);
            return;
        }

        this->scriptIDs = (u32*)heap->tryAlloc(sizeof(u32) * this->header.numScripts, sizeof(u32));
        OSBlockMove(this->scriptIDs, scriptIDBuffer, sizeof(u32) * this->header.numScripts, false);

        this->scripts = (CSScript*)heap->tryAlloc(sizeof(CSScript) * this->header.numScripts, sizeof(CSScript));
        OSBlockMove(this->scripts, scriptBuffer, sizeof(CSScript) * this->header.numScripts, false);

        PRINT("Size of scripts.wms: ", fmt::hex, size);

        size = size - sizeof(Header) - (sizeof(u32) * this->header.numScripts) - (sizeof(CSScript) * this->header.numScripts);
    
        u8* scriptDataBuffer = (u8*)heap->tryAlloc(size, align);

        bytesRead = handle.read(reinterpret_cast<u8*>(scriptDataBuffer), size);

        if (bytesRead != size) {
            PRINT(LogColor::Red, "scripts.wms script data read size mismatch, read size: ", fmt::hex, bytesRead, ", expected size: ", fmt::hex, size);
            return;
        }

        this->scriptsData = (CSScriptCommand*)heap->tryAlloc(size, sizeof(CSScriptCommand));
        OSBlockMove(this->scriptsData, scriptDataBuffer, size, false);
    
        heap->free(headerBuffer);
        heap->free(scriptIDBuffer);
        heap->free(scriptBuffer);
        heap->free(scriptDataBuffer);

        PRINT(header.numScripts, " scripts loaded.");
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

    WMSFile* wmsFile;
};
