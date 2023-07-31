#pragma once

#include "sead/idisposer.h"
#include "sead/safestring.h"
#include "sead/resource.h"
#include "sead/decompressor.h"

class ResMgr {
    SEAD_SINGLETON_DISPOSER(ResMgr);

private:
    class ResHolder : public sead::IDisposer {
    public:
        ResHolder(const sead::SafeString& key, sead::ArchiveRes* archive);

        virtual ~ResHolder() {
            ResMgr::instance()->remove(key);
        }

        sead::FixedSafeString<32> key;
        sead::ArchiveRes* archiveRes;
    };

    static_assert(sizeof(ResHolder) == 0x40);

public:
    ResMgr();

    bool loadLevelResPack(const sead::SafeString& levelName, sead::Heap* heap);
    bool isLevelArchiveResLoaded() const { return levelArchiveRes != nullptr; }
    sead::ArchiveRes* getLevelArchiveRes() const { return levelArchiveRes; }
    void* getFileFromLevelArchiveRes(const sead::SafeString& fileName, u32* length = nullptr) const;

    bool loadArchiveRes(const sead::SafeString& key, const sead::SafeString& filePath, sead::Heap* heap, bool isYaz0);
    bool isArchiveResLoaded(const sead::SafeString& key) const;
    sead::ArchiveRes* getArchiveRes(const sead::SafeString& key) const;
    void* getFileFromArchiveRes(const sead::SafeString& key, const sead::SafeString& fileName, u32* length = nullptr) const;
    void* getFileFromArchiveRes(sead::ArchiveRes* archive, const sead::SafeString& fileName, u32* length = nullptr) const;
    void remove(const sead::SafeString& key);

    sead::ArchiveRes* levelArchiveRes;
    u8 resHolderTreeMap[0x4414]; // sead::FixedStrTreeMap<32, ResHolder*, 256>
    sead::SZSDecompressor* decompressor;
};

static_assert(sizeof(ResMgr) == 0x442C, "ResMgr size mismatch");
