/*
#include "resource/seadSharcArchiveRes.h"
#include "tsuru/log.h"

namespace sead {

// * Custom function
void SharcArchiveRes::getFATEntryName(BufferedSafeString* outName, const FATEntry& entry) const {
    if (!outName)
        return;

    u32 offset = Endian::toHost(this->endianType, entry.nameOffset);
    if (offset == 0) {
        __os_snprintf(outName->getBuffer(), outName->getBufferSize(), "%08x", Endian::toHost(this->endianType, entry.hash));
        //outName->format("%08x", Endian::toHost(endianType, entry.hash));
    }
    else {
        if ((u8*)this->fntBlock + (offset & 0xFFFFFF) > this->dataBlock) {
            PRINT("Invalid data start offset");
            outName->clear();
        }
        else {
            //outName->copy(fntBlock + (offset & 0xFFFFFF) * cFileNameTableAlign);
            strncpy(outName->getBuffer(), this->fntBlock + (offset & 0xFFFFFF) * cFileNameTableAlign, outName->getBufferSize());
        }
    }
}

}
*/
