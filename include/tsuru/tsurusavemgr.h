#include <types.h>
#include <sead.h>

class TsuruSaveMgr {
public:
    struct TsuruSaveData {
        TsuruSaveData()
            : magic(0xCAFEF00D)
            , infiniteLivesEnabled(false)
            , infiniteTimeEnabled(false)
            , noClipEnabled(false)
            , invincibilityEnabled(false)
            , collisionViewerEnabled(false)
            , instantRespawnEnabled(false)
        { }

        u32 magic;                          // _0
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

    void init();
    void save();

    bool write();

    static void boot();

    static TsuruSaveData sSaveData;

    bool inited;
};
