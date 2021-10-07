#include <game/sound/sound.h>

void SetFxReverbHiAndDelay(void*, u32 sfxMode) {
    nw::snd::FxReverbHi::ReverbHiParam &reverbHiParam = SoundSystem::instance()->getAudioFx()->getReverbHiParam();
    nw::snd::FxDelay::DelayParam &delayParam = SoundSystem::instance()->getAudioFx()->getDelayParam();

    reverbHiParam.preDelayTime = 0.02f;
    reverbHiParam.fusedTime = 3.0f;
    reverbHiParam.coloration = 0.6f;
    reverbHiParam.damping = 0.4f;
    reverbHiParam.crosstalk = 0.1f;
    reverbHiParam.outGain = 1.0f;
    reverbHiParam.earlyMode = 5;
    reverbHiParam.preDelayTimeMax = 0.02f;
    reverbHiParam.fusedMode = 0;
    reverbHiParam.earlyGain = 0.0f;
    reverbHiParam.fusedGain = 1.0f;
    DefaultReverbHiParam = reverbHiParam;

    delayParam.delay = 160.0f;
    delayParam.feedback = 0.4f;
    delayParam.outGain = 1.0f;
    delayParam.maxDelay = 160.0f;
    delayParam.lpf = 1.0f;
    DefaultDelayParam = delayParam;

    switch (sfxMode) {
    case 0:
    default:
        reverbHiParam.fusedTime = 4.0f;
        reverbHiParam.damping = 0.0f;
        reverbHiParam.fusedMode = 5;

        delayParam.delay = 120.0f;
        delayParam.feedback = 0.1f;
        delayParam.maxDelay = 120.0f;

        SFXReverb_0 = 0.03f;
        SFXReverb_1 = 0.01f;
        SFXReverbPlyJump_0 = 0.04f;
        SFXReverbPlyJump_1 = 0.04f;
        return;
    case 1:
    case 11:
        reverbHiParam.fusedTime = 5.0f;
        reverbHiParam.fusedMode = 5;

        delayParam.delay = 180.0f;
        delayParam.feedback = 0.5f;
        delayParam.maxDelay = 180.0f;

        SFXReverb_0 = 0.04f;
        SFXReverb_1 = 0.1f;
        SFXReverbPlyJump_0 = 0.03f;
        SFXReverbPlyJump_1 = 0.05f;
        return;
    case 2:
        reverbHiParam.fusedTime = 1.2f;
        reverbHiParam.damping = 0.9f;
        reverbHiParam.fusedMode = 2;

        delayParam.delay = 100.0f;
        delayParam.feedback = 0.1f;
        delayParam.maxDelay = 100.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.07f;
        SFXReverbPlyJump_0 = 0.07f;
        SFXReverbPlyJump_1 = 0.07f;
        return;
    case 3:
        reverbHiParam.fusedTime = 3.0f;
        reverbHiParam.fusedMode = 2;

        delayParam.delay = 180.0f;
        delayParam.feedback = 0.3f;
        delayParam.maxDelay = 180.0f;

        SFXReverb_0 = 0.1f;
        SFXReverb_1 = 0.1f;
        SFXReverbPlyJump_0 = 0.03f;
        SFXReverbPlyJump_1 = 0.1f;
        return;
    case 4:
        reverbHiParam.damping = 0.2f;
        reverbHiParam.fusedMode = 3;

        delayParam.delay = 200.0f;
        delayParam.feedback = 0.38f;
        delayParam.maxDelay = 200.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.08f;
        SFXReverbPlyJump_0 = 0.07f;
        SFXReverbPlyJump_1 = 0.04f;
        return;
    case 5:
        reverbHiParam.damping = 0.9f;
        reverbHiParam.fusedMode = 3;

        delayParam.delay = 190.0f;
        delayParam.feedback = 0.4f;
        delayParam.maxDelay = 190.0f;

        SFXReverb_0 = 0.05f;
        SFXReverb_1 = 0.12f;
        SFXReverbPlyJump_0 = 0.05f;
        SFXReverbPlyJump_1 = 0.07f;
        return;
    case 6:
        reverbHiParam.damping = 0.1f;
        reverbHiParam.fusedMode = 4;

        delayParam.delay = 190.0f;
        delayParam.feedback = 0.3f;
        delayParam.maxDelay = 190.0f;

        SFXReverb_0 = 0.1f;
        SFXReverb_1 = 0.13f;
        SFXReverbPlyJump_0 = 0.1f;
        SFXReverbPlyJump_1 = 0.08f;
        return;
    case 7:
        reverbHiParam.fusedTime = 2.5f;
        reverbHiParam.fusedMode = 2;

        delayParam.delay = 94.0f;
        delayParam.feedback = 0.13f;
        delayParam.maxDelay = 94.0f;

        SFXReverb_0 = 0.06f;
        SFXReverb_1 = 0.17f;
        SFXReverbPlyJump_0 = 0.06f;
        SFXReverbPlyJump_1 = 0.17f;
        return;
    case 8:
        reverbHiParam.fusedTime = 1.8f;
        reverbHiParam.coloration = 0.4f;
        reverbHiParam.fusedMode = 1;

        delayParam.delay = 32.0f;
        delayParam.feedback = 0.83f;
        delayParam.maxDelay = 100.0f;

        SFXReverb_0 = 0.04f;
        SFXReverb_1 = 0.08f;
        SFXReverbPlyJump_0 = 0.04f;
        SFXReverbPlyJump_1 = 0.1f;
        return;
    case 9:
        reverbHiParam.fusedTime = 1.0f;
        reverbHiParam.fusedMode = 5;

        delayParam.delay = 350.0f;
        delayParam.feedback = 0.1f;
        delayParam.maxDelay = 350.0f;

        SFXReverb_0 = 0.01f;
        SFXReverb_1 = 0.02f;
        SFXReverbPlyJump_0 = 0.01f;
        SFXReverbPlyJump_1 = 0.02f;
        return;
    case 10:
        reverbHiParam.fusedTime = 0.3f;
        reverbHiParam.fusedMode = 2;

        delayParam.delay = 22.0f;
        delayParam.feedback = 0.4f;
        delayParam.maxDelay = 60.0f;

        SFXReverb_0 = 0.1f;
        SFXReverb_1 = 0.15f;
        SFXReverbPlyJump_0 = 0.1f;
        SFXReverbPlyJump_1 = 0.15f;
        return;
    case 12:
        reverbHiParam.fusedTime = 0.8f;
        reverbHiParam.fusedMode = 2;

        delayParam.delay = 39.0f;
        delayParam.feedback = 0.3f;
        delayParam.maxDelay = 39.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.15f;
        SFXReverbPlyJump_0 = 0.07f;
        SFXReverbPlyJump_1 = 0.15f;
        return;
    case 13:
        reverbHiParam.fusedTime = 3.5f;
        reverbHiParam.fusedMode = 5;

        delayParam.delay = 180.0f;
        delayParam.feedback = 0.4f;
        delayParam.maxDelay = 180.0f;

        SFXReverb_0 = 0.07f;
        SFXReverb_1 = 0.15f;
        SFXReverbPlyJump_0 = 0.05f;
        SFXReverbPlyJump_1 = 0.1f;
        return;
    case 14:
        reverbHiParam.fusedTime = 5.0f;
        reverbHiParam.fusedMode = 5;

        delayParam.delay = 180.0f;
        delayParam.feedback = 0.5f;
        delayParam.maxDelay = 180.0f;

        SFXReverb_0 = 0.04f;
        SFXReverb_1 = 0.08f;
        SFXReverbPlyJump_0 = 0.04f;
        SFXReverbPlyJump_1 = 0.08f;
    }
}
