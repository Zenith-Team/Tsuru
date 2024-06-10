#pragma once

#include "game/sound/sndobject.h"
#include "game/sound/effects.h"

class GameAudio {
public:
    class SndObjectCommonEmy : public SndObjectCommon<12> {
    public:
        SndObjectCommonEmy()
            : SndObjectCommon<12>(1)
        { }

        virtual ~SndObjectCommonEmy(); // deleted

        // Does the stagePos -> screenPos conversion
        nw::snd::SoundHandle* startSoundStage(const char* label, const sead::Vector2f& stagePos, u32 remotePlayer) override;
        // Does the stagePos -> screenPos conversion
        nw::snd::SoundHandle* startSoundStage(const char* label, const sead::Vector2f& stagePos, u16, u32 remotePlayer) override; // deleted

        nw::snd::SoundHandle* startSound(const char* label, const sead::Vector2f& screenPos, u32 remotePlayer);
        nw::snd::SoundHandle* startSound(const char* label, const sead::Vector2f& screenPos, u16, u32 remotePlayer);
    
        nw::snd::SoundHandle* holdSound(const char* label, s32 id, const sead::Vector2f& screenPos, u32 remotePlayer);
        nw::snd::SoundHandle* holdSound(const char* label, s32 id, const sead::Vector2f& screenPos, u16, u32 remotePlayer);

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
        nw::snd::SoundHandle* startSoundStage(const char* label, const sead::Vector2f& stagePos, u32 remotePlayer) override;
        // Does the stagePos -> screenPos conversion
        nw::snd::SoundHandle* startSoundStage(const char* label, const sead::Vector2f& stagePos, u16, u32 remotePlayer) override;

        nw::snd::SoundHandle* startSound(const char* label, const sead::Vector2f& screenPos, u32 remotePlayer);
        nw::snd::SoundHandle* startSound(const char* label, const sead::Vector2f& screenPos, u16, u32 remotePlayer);
    
        nw::snd::SoundHandle* holdSound(const char* label, s32 id, const sead::Vector2f& screenPos, u32 remotePlayer);
        nw::snd::SoundHandle* holdSound(const char* label, s32 id, const sead::Vector2f& screenPos, u16, u32 remotePlayer);

        static SndObjectCommonMap* instance() {
            return sInstance;
        }

    private:
        static SndObjectCommonMap* sInstance;
    };

public:
    void loadSceneSnd();

    static void initSound();
    static void execute();
    static void setPause(u32 fadeFrames);

    // Converts stage position to screen position
    // @param out Output sead::Vector2f variable
    // @param stagePos Position to be converted
    static void convertSndObjectPos(sead::Vector2f* out, const sead::Vector2f& stagePos);

    // Converts stage position to screen position
    // @param out Output sead::Vector2f variable
    // @param stagePos Position to be converted
    static inline void convertSndObjectPos(sead::Vector2f* out, const sead::Vector3f& stagePos) {
        convertSndObjectPos(out, sead::Vector2f(stagePos.x, stagePos.y));
    }

    // Gets the wii remote controller id corresponding to the player id
    static u32 getRemotePlayer(u32 playerID);

    static inline nw::snd::SoundHandle* startSoundEmy(const char* label, const sead::Vector2f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, stagePos);
        return SndObjectCommonEmy::instance()->startSound(label, screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* startSoundEmy(const char* label, const sead::Vector3f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, sead::Vector2f(stagePos.x, stagePos.y));
        return SndObjectCommonEmy::instance()->startSound(label, screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* startSoundMap(const char* label, const sead::Vector2f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, stagePos);
        return SndObjectCommonMap::instance()->startSound(label, screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* startSoundMap(const char* label, const sead::Vector3f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, sead::Vector2f(stagePos.x, stagePos.y));
        return SndObjectCommonMap::instance()->startSound(label, screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* holdSoundEmy(const char* label, s32 id, const sead::Vector2f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, stagePos);
        return SndObjectCommonEmy::instance()->holdSound(label, id, screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* holdSoundEmy(const char* label, s32 id, const sead::Vector3f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, sead::Vector2f(stagePos.x, stagePos.y));
        return SndObjectCommonEmy::instance()->holdSound(label, id, screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* holdSoundMap(const char* label, s32 id, const sead::Vector2f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, stagePos);
        return SndObjectCommonMap::instance()->holdSound(label, id, screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* holdSoundMap(const char* label, s32 id, const sead::Vector3f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, sead::Vector2f(stagePos.x, stagePos.y));
        return SndObjectCommonMap::instance()->holdSound(label, id, screenPos, remotePlayer);
    }

    // Those probably don't exit

    static inline nw::snd::SoundHandle* startSoundEmy(SoundEffects::IDs id, const sead::Vector2f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, stagePos);
        return SndObjectCommonEmy::instance()->startSound(SoundEffects::getName(id), screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* startSoundEmy(SoundEffects::IDs id, const sead::Vector3f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, sead::Vector2f(stagePos.x, stagePos.y));
        return SndObjectCommonEmy::instance()->startSound(SoundEffects::getName(id), screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* startSoundMap(SoundEffects::IDs id, const sead::Vector2f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, stagePos);
        return SndObjectCommonMap::instance()->startSound(SoundEffects::getName(id), screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* startSoundMap(SoundEffects::IDs id, const sead::Vector3f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, sead::Vector2f(stagePos.x, stagePos.y));
        return SndObjectCommonMap::instance()->startSound(SoundEffects::getName(id), screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* holdSoundEmy(SoundEffects::IDs soundID, s32 id, const sead::Vector2f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, stagePos);
        return SndObjectCommonEmy::instance()->holdSound(SoundEffects::getName(soundID), id, screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* holdSoundEmy(SoundEffects::IDs soundID, s32 id, const sead::Vector3f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, sead::Vector2f(stagePos.x, stagePos.y));
        return SndObjectCommonEmy::instance()->holdSound(SoundEffects::getName(soundID), id, screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* holdSoundMap(SoundEffects::IDs soundID, s32 id, const sead::Vector2f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, stagePos);
        return SndObjectCommonMap::instance()->holdSound(SoundEffects::getName(soundID), id, screenPos, remotePlayer);
    }

    static inline nw::snd::SoundHandle* holdSoundMap(SoundEffects::IDs soundID, s32 id, const sead::Vector3f& stagePos, u32 remotePlayer = 1) {
        sead::Vector2f screenPos;
        convertSndObjectPos(&screenPos, sead::Vector2f(stagePos.x, stagePos.y));
        return SndObjectCommonMap::instance()->holdSound(SoundEffects::getName(soundID), id, screenPos, remotePlayer);
    }
};
