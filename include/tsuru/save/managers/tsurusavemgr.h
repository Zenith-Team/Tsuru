#pragma once

#include "tsuru/save/system/customsavemgr.h"
#include "heap/seadDisposer.h"

class TsuruSaveMgr : public CustomSaveMgr {
public:
    struct TsuruSaveData : CustomSaveData {
        TsuruSaveData()
            : CustomSaveData()
            , infiniteLivesEnabled(false)
            , infiniteTimeEnabled(false)
            , noClipEnabled(false)
            , invincibilityEnabled(false)
            , collisionViewerEnabled(false)
            , instantRespawnEnabled(false)
            , switchBlockBlue()
            , locationViewerEnabled(false)
            , pathViewerEnabled(false)
        { }

        bool infiniteLivesEnabled;
        bool infiniteTimeEnabled;
        bool noClipEnabled;
        bool invincibilityEnabled;
        bool collisionViewerEnabled;
        bool instantRespawnEnabled;
        bool switchBlockBlue[6];
        bool locationViewerEnabled;
        bool pathViewerEnabled;
    };

public:
    SEAD_SINGLETON_DISPOSER(TsuruSaveMgr);

public:
    TsuruSaveMgr();

    u32 getSaveDataSize() override;
    void remakeSaveData() override;

    static TsuruSaveData sSaveData;
};
