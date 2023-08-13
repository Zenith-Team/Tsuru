#pragma once

#include "sead/taskparameter.h"
#include "sead/offsetlist.h"

namespace sead {

class AudioSystem;
class AudioResetter;
class AudioPlayer;
class AudioResourceLoader;
class AudioSubsetBase;

class AudioSettingParameter : public TaskParameter {
    SEAD_RTTI_OVERRIDE(AudioSettingParameter, TaskParameter);
    
public:
    AudioSettingParameter();

    void setAudioSystem(AudioSystem* audioSystem);
    void setResetter(AudioResetter* resetter);
    void setPlayer(AudioPlayer* player);
    void setResourceLoader(AudioResourceLoader* resourceLoader);
    void appendSubset(AudioSubsetBase* subset);

    AudioSystem* audioSystem;
    AudioResetter* resetter;
    AudioPlayer* player;
    AudioResourceLoader* resourceLoader;
    OffsetList<AudioSubsetBase> subsets;
};

static_assert(sizeof(AudioSettingParameter) == 0x24, "sead::AudioSettingParameter size mismatch");

}
