#pragma once

#include "tsuru/save/system/customsavemgr.h"
#include "sead/idisposer.h"

class CarterraSaveMgr : public CustomSaveMgr {
public:
    struct CarterraSaveData : public CustomSaveData {
        ENUM_CLASS(LevelCompletion,
            NormalExit = 1 << 0,
            SecretExit = 1 << 1
        );
        
        struct SaveSlot {
            SaveSlot()
                : lastMap(1)
                , lastNode(0)
                , levelCompletions()
            { }

            u32 lastMap;
            u32 lastNode;
            u8 levelCompletions[9][58];
        };

        CarterraSaveData()
            : CustomSaveData()
            , saveSlots()
        { }

        SaveSlot saveSlots[3*4];
    };

public:
    SEAD_SINGLETON_DISPOSER(CarterraSaveMgr);

public:
    CarterraSaveMgr();

    u32 getSaveDataSize() override;
    void remakeSaveData() override;

    static CarterraSaveData sSaveData;
};
