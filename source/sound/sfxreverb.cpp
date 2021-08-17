#include <game/sound.h>

extern nw::snd::internal::FxReverbHiParam DefaultReverbHiParam;
extern nw::snd::internal::FxDelayParam DefaultDelayParam;

extern f32 SFXReverb_0;
extern f32 SFXReverb_1;
extern f32 SFXReverbPlyJump_0;
extern f32 SFXReverbPlyJump_1;

void SetFxReverbHiAndDelay(void*, u32 sfxMode) {
    nw::snd::internal::FxReverbHiParam &reverbHiParam = SoundSystem::sInstance->getAudioFx()->getReverbHiParam();
    nw::snd::internal::FxDelayParam &delayParam = SoundSystem::sInstance->getAudioFx()->getDelayParam();

    reverbHiParam.mPreDelayTime = 0.02f;
    reverbHiParam.mFusedTime = 3.0f;
    reverbHiParam.mColoration = 0.6f;
    reverbHiParam.mDamping = 0.4f;
    reverbHiParam.mCrosstalk = 0.1f;
    reverbHiParam.mOutGain = 1.0f;
    reverbHiParam.mEarlyMode = 5;
    reverbHiParam.mPreDelayTimeMax = 0.02f;
    reverbHiParam.mFusedMode = 0;
    reverbHiParam.mEarlyGain = 0.0f;
    reverbHiParam.mFusedGain = 1.0f;
    DefaultReverbHiParam = reverbHiParam;

    delayParam.mDelay = 160.0f;
    delayParam.mFeedback = 0.4f;
    delayParam.mOutGain = 1.0f;
    delayParam.mMaxDelay = 160.0f;
    delayParam.mLpf = 1.0f;
    DefaultDelayParam = delayParam;

    switch (sfxMode) {
    case 0:
    default:
        reverbHiParam.mFusedTime = 4.0f;
        reverbHiParam.mDamping = 0.0f;
        reverbHiParam.mFusedMode = 5;

        delayParam.mDelay = 120.0f;
        delayParam.mFeedback = 0.1f;
        delayParam.mMaxDelay = 120.0f;

        SFXReverb_0 = 0.03f;
        SFXReverb_1 = 0.01f;
        SFXReverbPlyJump_0 = 0.04f;
        SFXReverbPlyJump_1 = 0.04f;
        return;
    case 1:
    case 11:
        reverbHiParam.mFusedTime = 5.0f;
        reverbHiParam.mFusedMode = 5;

        delayParam.mDelay = 180.0f;
        delayParam.mFeedback = 0.5f;
        delayParam.mMaxDelay = 180.0f;

        SFXReverb_0 = 0.04f;
        SFXReverb_1 = 0.1f;
        SFXReverbPlyJump_0 = 0.03f;
        SFXReverbPlyJump_1 = 0.05f;
        return;
    case 2:
        reverbHiParam.mFusedTime = 1.2f;
        reverbHiParam.mDamping = 0.9f;
        reverbHiParam.mFusedMode = 2;

        delayParam.mDelay = 100.0f;
        delayParam.mFeedback = 0.1f;
        delayParam.mMaxDelay = 100.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.07f;
        SFXReverbPlyJump_0 = 0.07f;
        SFXReverbPlyJump_1 = 0.07f;
        return;
    case 3:
        reverbHiParam.mFusedTime = 3.0f;
        reverbHiParam.mFusedMode = 2;

        delayParam.mDelay = 180.0f;
        delayParam.mFeedback = 0.3f;
        delayParam.mMaxDelay = 180.0f;

        SFXReverb_0 = 0.1f;
        SFXReverb_1 = 0.1f;
        SFXReverbPlyJump_0 = 0.03f;
        SFXReverbPlyJump_1 = 0.1f;
        return;
    case 4:
        reverbHiParam.mDamping = 0.2f;
        reverbHiParam.mFusedMode = 3;

        delayParam.mDelay = 200.0f;
        delayParam.mFeedback = 0.38f;
        delayParam.mMaxDelay = 200.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.08f;
        SFXReverbPlyJump_0 = 0.07f;
        SFXReverbPlyJump_1 = 0.04f;
        return;
    case 5:
        reverbHiParam.mDamping = 0.9f;
        reverbHiParam.mFusedMode = 3;

        delayParam.mDelay = 190.0f;
        delayParam.mFeedback = 0.4f;
        delayParam.mMaxDelay = 190.0f;

        SFXReverb_0 = 0.05f;
        SFXReverb_1 = 0.12f;
        SFXReverbPlyJump_0 = 0.05f;
        SFXReverbPlyJump_1 = 0.07f;
        return;
    case 6:
        reverbHiParam.mDamping = 0.1f;
        reverbHiParam.mFusedMode = 4;

        delayParam.mDelay = 190.0f;
        delayParam.mFeedback = 0.3f;
        delayParam.mMaxDelay = 190.0f;

        SFXReverb_0 = 0.1f;
        SFXReverb_1 = 0.13f;
        SFXReverbPlyJump_0 = 0.1f;
        SFXReverbPlyJump_1 = 0.08f;
        return;
    case 7:
        reverbHiParam.mFusedTime = 2.5f;
        reverbHiParam.mFusedMode = 2;

        delayParam.mDelay = 94.0f;
        delayParam.mFeedback = 0.13f;
        delayParam.mMaxDelay = 94.0f;

        SFXReverb_0 = 0.06f;
        SFXReverb_1 = 0.17f;
        SFXReverbPlyJump_0 = 0.06f;
        SFXReverbPlyJump_1 = 0.17f;
        return;
    case 8:
        reverbHiParam.mFusedTime = 1.8f;
        reverbHiParam.mColoration = 0.4f;
        reverbHiParam.mFusedMode = 1;

        delayParam.mDelay = 32.0f;
        delayParam.mFeedback = 0.83f;
        delayParam.mMaxDelay = 100.0f;

        SFXReverb_0 = 0.04f;
        SFXReverb_1 = 0.08f;
        SFXReverbPlyJump_0 = 0.04f;
        SFXReverbPlyJump_1 = 0.1f;
        return;
    case 9:
        reverbHiParam.mFusedTime = 1.0f;
        reverbHiParam.mFusedMode = 5;

        delayParam.mDelay = 350.0f;
        delayParam.mFeedback = 0.1f;
        delayParam.mMaxDelay = 350.0f;

        SFXReverb_0 = 0.01f;
        SFXReverb_1 = 0.02f;
        SFXReverbPlyJump_0 = 0.01f;
        SFXReverbPlyJump_1 = 0.02f;
        return;
    case 10:
        reverbHiParam.mFusedTime = 0.3f;
        reverbHiParam.mFusedMode = 2;

        delayParam.mDelay = 22.0f;
        delayParam.mFeedback = 0.4f;
        delayParam.mMaxDelay = 60.0f;

        SFXReverb_0 = 0.1f;
        SFXReverb_1 = 0.15f;
        SFXReverbPlyJump_0 = 0.1f;
        SFXReverbPlyJump_1 = 0.15f;
        return;
    case 12:
        reverbHiParam.mFusedTime = 0.8f;
        reverbHiParam.mFusedMode = 2;

        delayParam.mDelay = 39.0f;
        delayParam.mFeedback = 0.3f;
        delayParam.mMaxDelay = 39.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.15f;
        SFXReverbPlyJump_0 = 0.07f;
        SFXReverbPlyJump_1 = 0.15f;
        return;
    case 13:
        reverbHiParam.mFusedTime = 3.5f;
        reverbHiParam.mFusedMode = 5;

        delayParam.mDelay = 180.0f;
        delayParam.mFeedback = 0.4f;
        delayParam.mMaxDelay = 180.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.15f;
        SFXReverbPlyJump_0 = 0.05f;
        SFXReverbPlyJump_1 = 0.1f;
        return;
    case 14:
        reverbHiParam.mFusedTime = 5.0f;
        reverbHiParam.mFusedMode = 5;

        delayParam.mDelay = 180.0f;
        delayParam.mFeedback = 0.5f;
        delayParam.mMaxDelay = 180.0f;

        SFXReverb_0 = 0.04f;
        SFXReverb_1 = 0.08f;
        SFXReverbPlyJump_0 = 0.04f;
        SFXReverbPlyJump_1 = 0.08f;
    }
}
