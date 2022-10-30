#include "tsuru/cobra.h"
#include "game/actor/actormgr.h"

const Profile CSScriptLoaderProfile(&CSScriptLoader::build, ProfileID::CSScriptLoader);
CSScriptLoader* CSScriptLoader::instance = nullptr;

CSScriptLoader::CSScriptLoader(const ActorBuildInfo* buildInfo)
    : CourseSelectActor(buildInfo)
    , wmsFile(nullptr)
{ }

Actor* CSScriptLoader::build(const ActorBuildInfo* buildInfo) {
    return new CSScriptLoader(buildInfo);
}

u32 CSScriptLoader::onCreate() {
    instance = this;
    this->wmsFile = new WMSFile(this->heap);

    return 1;
}

void loadCustomCSScripts() {
    ActorBuildInfo buildInfo = { 0 };

    buildInfo.profile = Profile::get(ProfileID::CSScriptLoader);
    ActorMgr::instance()->create(buildInfo);
}
