#pragma once

#include "sead/resource.h"
#include "sead/buffer.h"
#include "sead/endian.h"

namespace sead {

class SharcArchiveRes : public ArchiveRes {
    SEAD_RTTI_OVERRIDE(SharcArchiveRes, ArchiveRes);

public:
    static const u32 cArchiveVersion = 0x100;
    static const u32 cArchiveEntryMax = 0x3fff;
    static const u32 cFileNameTableAlign = 4;

public:
    struct ArchiveBlockHeader {
        char signature[4];
        u16 headerSize;
        u16 byteOrder;
        u32 fileSize;
        u32 dataBlockOffset;
        u16 version;
        u16 reserved;
    };
    static_assert(sizeof(ArchiveBlockHeader) == 0x14, "sead::SharcArchiveRes::ArchiveBlockHeader size mismatch");

    struct FATBlockHeader {
        char signature[4];
        u16 headerSize;
        u16 fileNum;
        u32 hashKey;
    };
    static_assert(sizeof(FATBlockHeader) == 0xC, "sead::SharcArchiveRes::FATBlockHeader size mismatch");

    struct FATEntry {
        u32 hash;
        u32 nameOffset;
        u32 dataStartOffset;
        u32 dataEndOffset;
    };
    static_assert(sizeof(FATEntry) == 0x10, "sead::SharcArchiveRes::FATEntry size mismatch");

    struct FNTBlockHeader {
        char signature[4];
        u16 headerSize;
        u16 reserved;
    };
    static_assert(sizeof(FNTBlockHeader) == 8, "sead::SharcArchiveRes::FNTBlockHeader size mismatch");

public:
    SharcArchiveRes();
    virtual ~SharcArchiveRes();

protected:
    virtual void* getFileImpl_(const SafeString& filePath, FileInfo* fileInfo);
    virtual void* getFileFastImpl_(s32 entryId, FileInfo* fileInfo);
    virtual s32 convertPathToEntryIDImpl_(const SafeString& filePath);
    virtual bool setCurrentDirectoryImpl_(const SafeString& filePath);
    virtual bool openDirectoryImpl_(HandleBuffer* handleBuffer, const SafeString& dirPath);
    virtual bool closeDirectoryImpl_(HandleBuffer* handleBuffer);
    virtual u32 readDirectoryImpl_(HandleBuffer* handleBuffer, DirectoryEntry* entry, u32 num);
    virtual bool prepareArchive_(const void* archive);

public:
    void getFATEntryName(BufferedSafeString* outName, const FATEntry& entry) const; // custom

    const ArchiveBlockHeader* archiveBlockHeader;
    const FATBlockHeader* fatBlockHeader;
    const char* fntBlock;
    Buffer<const FATEntry> fatEntrys;
    const u8* dataBlock;
    Endian::EndianType endianType;
};

static_assert(sizeof(SharcArchiveRes) == 0x44, "sead::SharcArchiveRes size mismatch");

}
