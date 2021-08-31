#include <types.h>
#include <sead.h>

class SHSaveMgr {
public:
    struct SHSaveData {
        SHSaveData()
            : magic(0xCAFEF00D) // ツ
            , testData(0xabcdef)
        { }

        u32 magic;
        u32 testData;
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
