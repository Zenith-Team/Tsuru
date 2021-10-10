#include <tsuru/save/customsavemgr.h>
#include <sead/idisposer.h>

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

        bool infiniteLivesEnabled;          // _4
        bool infiniteTimeEnabled;           // _5
        bool noClipEnabled;                 // _6
        bool invincibilityEnabled;          // _7
        bool collisionViewerEnabled;        // _8
        bool instantRespawnEnabled;         // _9
    };

public:
    SEAD_SINGLETON_DISPOSER(TsuruSaveMgr)

public:
    TsuruSaveMgr();

    u32 getSaveDataSize() override;
    void remakeSaveData() override;

    static TsuruSaveData sSaveData;
};
