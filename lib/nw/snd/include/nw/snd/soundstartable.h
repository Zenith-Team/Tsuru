#pragma once

#include "nw/snd/global.h"

namespace nw { namespace snd {

class SoundHandle;

class SoundStartable {
public:
    struct StartInfo {
        enum EnableFlagBig {
            // ...
            Enable_WaveSoundInfo = 1 << 6,
            // ...
        };

        struct SeqSoundInfo {
            SeqSoundInfo()
                : seqDataAddress(nullptr)
                , startLocationLabel(nullptr)
            {
                for (u32 i = 0; i < 4; i++)
                {
                    bankIDs[i] = 0xFFFFFFFF;
                }
            }

            void* seqDataAddress;
            const char* startLocationLabel;
            u32 bankIDs[4];
        };

        struct StreamSoundInfo {
            StreamSoundInfo()
                : _0(0)
                , _4(0)
            { }

            u32 _0;
            u32 _4;
        };

        struct WaveSoundInfo {
            WaveSoundInfo()
                : waveAddress(nullptr)
                , _4(0)
                , _8(0)
                , waveType(WaveType_Invalid)
            { }

            void* waveAddress;
            u32 _4;
            u8 _8;
            s8 waveType;
        };

        StartInfo()
            : enableFlag(0)
            , voiceRendererType(0)
        { }

        u32 enableFlag;
        u32 startOffsetType;
        s32 startOffset;
        u32 playerID;
        s32 playerPriority;
        s32 actorPlayerID;
        SeqSoundInfo seqSoundInfo;
        StreamSoundInfo streamSoundInfo;
        WaveSoundInfo waveSoundInfo;
        u8 voiceRendererType;
    };

    class StartResult {
    public:
        enum ResultCode {
            START_SUCCESS = 0,
            START_ERR_LOW_PRIORITY,
            START_ERR_INVALID_LABEL_STRING,
            START_ERR_INVALID_SOUNDID,
            START_ERR_NOT_DATA_LOADED,
            START_ERR_NOT_SEQ_LOADED,
            START_ERR_NOT_BANK_LOADED,
            START_ERR_NOT_WSD_LOADED,
            START_ERR_NOT_WARC_LOADED,
            START_ERR_NOT_ENOUGH_PLAYER_HEAP,
            START_ERR_CANNOT_OPEN_FILE,
            START_ERR_NOT_AVAILABLE,
            START_ERR_CANNOT_ALLOCATE_TRACK,
            START_ERR_NOT_ENOUGH_INSTANCE,
            START_ERR_INVALID_PARAMETER,
            START_ERR_INVALID_SEQ_START_LOCATION_LABEL,
            START_ERR_ACTOR_NOT_INITIALIZED,
            START_ERR_INVALID_WARC_ID,
            START_ERR_INVALID_BANK_DATA,
            START_ERR_USER = 128,
            START_ERR_UNKNOWN = 255
        };
    };

public:
    virtual ~SoundStartable();
    virtual StartResult detail_SetupSound(SoundHandle* handle, u32 soundID, bool holdFlag, const StartInfo* startInfo) = 0;
    virtual u32 detail_GetItemID(const char* string) = 0;

    u32 StartSound(SoundHandle* handle, u32 soundID, StartInfo* startInfo);
    u32 StartSound(SoundHandle* handle, const char* soundName, StartInfo* startInfo);
    u32 HoldSound(SoundHandle* handle, u32 soundID, StartInfo* startInfo);
    u32 HoldSound(SoundHandle* handle, const char* soundName, StartInfo* startInfo);
    u32 PrepareSound(SoundHandle* handle, u32 soundID, StartInfo* startInfo);
    u32 PrepareSound(SoundHandle* handle, const char* soundName, StartInfo* startInfo);
};

static_assert(sizeof(SoundStartable) == 0x4, "nw::snd::SoundStartable size mismatch");

} }
