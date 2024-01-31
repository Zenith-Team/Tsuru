#pragma once

typedef unsigned char u8;
typedef unsigned int u32;

#ifdef __cplusplus
extern "C" {
#endif

#define FFL_MIIDATA_PACKET_SIZE (0x60)

typedef struct FFLStoreData {
    union {
        u8 data[FFL_MIIDATA_PACKET_SIZE];
        u32 value32[FFL_MIIDATA_PACKET_SIZE / sizeof(u32)];
    };
} FFLStoreData;

#ifdef __cplusplus
}
#endif
