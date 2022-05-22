#pragma once

#include "tsuru/save/system/customsavemgr.h"
#include "sead/idisposer.h"

class TsuruSaveMgr : public CustomSaveMgr {
public:
    struct TsuruSaveData : CustomSaveData {
    private:
        TsuruSaveData()
            : CustomSaveData()
            , infiniteLivesEnabled(false)
            , infiniteTimeEnabled(false)
            , noClipEnabled(false)
            , invincibilityEnabled(false)
            , collisionViewerEnabled(false)
            , instantRespawnEnabled(false)
        { }

    public:
        friend class TsuruSaveMgr;

        bool infiniteLivesEnabled;          // 4
        bool infiniteTimeEnabled;           // 5
        bool noClipEnabled;                 // 6
        bool invincibilityEnabled;          // 7
        bool collisionViewerEnabled;        // 8
        bool instantRespawnEnabled;         // 9
    };

public:
    SEAD_SINGLETON_DISPOSER(TsuruSaveMgr)

public:
    TsuruSaveMgr();

    u32 getSaveDataSize() override;
    void remakeSaveData() override;

    static TsuruSaveData sSaveData;
};
