#include "sead/sharcarchiveres.h"
#include "log.h"

namespace sead {

// custom
void SharcArchiveRes::getFATEntryName(BufferedSafeString* outName, const FATEntry& entry) const {
    if (!outName)
        return;

    u32 offset = Endian::toHost(endianType, entry.nameOffset);
    if (offset == 0) {
        __os_snprintf(outName->getBuffer(), outName->getBufferSize(), "%08x", Endian::toHost(endianType, entry.hash));
        //outName->format("%08x", Endian::toHost(endianType, entry.hash));
    }
    else {
        if ((u8*)fntBlock + (offset & 0xFFFFFF) > dataBlock) {
            PRINT("Invalid data start offset");
            outName->clear();
        }
        else {
            //outName->copy(fntBlock + (offset & 0xFFFFFF) * cFileNameTableAlign);
            strncpy(outName->getBuffer(), fntBlock + (offset & 0xFFFFFF) * cFileNameTableAlign, outName->getBufferSize());
        }
    }
}

}
