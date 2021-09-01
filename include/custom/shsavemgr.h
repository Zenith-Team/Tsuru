#include <types.h>
#include <sead.h>

class SHSaveMgr {
public:
    struct SHSaveData {
        SHSaveData()
            : magic(0xCAFEF00D)
            , infiniteLivesEnabled(false)
            , infiniteTimeEnabled(false)
            , noClipEnabled(false)
            , invincibilityEnabled(false)
            , collisionViewerEnabled(false)
        { }

        u32 magic;                     // _0
        bool infiniteLivesEnabled;     // _4
        bool infiniteTimeEnabled;      // _5
        bool noClipEnabled;            // _6
        bool invincibilityEnabled;     // _7
        bool collisionViewerEnabled;   // _8
    };

public:
    SEAD_SINGLETON_DISPOSER(SHSaveMgr)

public:
    SHSaveMgr();

    void init();
    void save();

    static void boot();

    static SHSaveData sSaveData;
    
    bool mInited;
};
