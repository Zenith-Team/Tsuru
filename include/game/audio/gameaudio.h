#pragma once

#include "game/sound/sndobject.h"

class GameAudio {
public:
    class SndObjectCommonEmy : public SndObjectCommon<12> {
    public:
        SndObjectCommonEmy()
            : SndObjectCommon<12>(1)
        { }

        virtual ~SndObjectCommonEmy(); // deleted

        // Does the stagePos -> screenPos conversion
        SoundHandlePrm* startSoundStage(const char* label, const Vec2f& stagePos, u32 remotePlayer) override;
        // Does the stagePos -> screenPos conversion
        SoundHandlePrm* startSoundStage(const char* label, const Vec2f& stagePos, u16, u32 remotePlayer) override; // deleted

        SoundHandlePrm* startSound(const char* label, const Vec2f& screenPos, u32 remotePlayer);
        SoundHandlePrm* startSound(const char* label, const Vec2f& screenPos, u16, u32 remotePlayer);
    
        SoundHandlePrm* holdSound(const char* label, s32 id, const Vec2f& screenPos, u32 remotePlayer);
        SoundHandlePrm* holdSound(const char* label, s32 id, const Vec2f& screenPos, u16, u32 remotePlayer);

        static SndObjectCommonEmy* instance() {
            return sInstance;
        }

    private:
        static SndObjectCommonEmy* sInstance;
    };

    class SndObjectCommonMap : public SndObjectCommon<12> {
    public:
        SndObjectCommonMap()
            : SndObjectCommon<12>(1)
        { }

        virtual ~SndObjectCommonMap(); // deleted: nullptr for some reason

        // Does the stagePos -> screenPos conversion
        SoundHandlePrm* startSoundStage(const char* label, const Vec2f& stagePos, u32 remotePlayer) override;
        // Does the stagePos -> screenPos conversion
        SoundHandlePrm* startSoundStage(const char* label, const Vec2f& stagePos, u16, u32 remotePlayer) override;

        SoundHandlePrm* startSound(const char* label, const Vec2f& screenPos, u32 remotePlayer);
        SoundHandlePrm* startSound(const char* label, const Vec2f& screenPos, u16, u32 remotePlayer);
    
        SoundHandlePrm* holdSound(const char* label, s32 id, const Vec2f& screenPos, u32 remotePlayer);
        SoundHandlePrm* holdSound(const char* label, s32 id, const Vec2f& screenPos, u16, u32 remotePlayer);

        static SndObjectCommonMap* instance() {
            return sInstance;
        }

    private:
        static SndObjectCommonMap* sInstance;
    };

    // Converts stage position to screen position
    // @param out Output Vec2f variable
    // @param stagePos Position to be converted
    static void convertSndObjPos(Vec2f* out, const Vec2f& stagePos);

    // Converts stage position to screen position
    // @param out Output Vec2f variable
    // @param stagePos Position to be converted
    static inline void convertSndObjPos(Vec2f* out, const Vec3f& stagePos) {
        convertSndObjPos(out, Vec2f(stagePos.x, stagePos.y));
    }

    // Gets the wii remote controller id corresponding to the player id
    static u32 getRemotePlayer(u32 playerID);
};
