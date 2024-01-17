#include "game/distantview/distantviewmgr.h"
#include "game/actor/actor.h"
#include "log.h"

class ShaderController : public Actor {
    SEAD_RTTI_OVERRIDE_IMPL(ShaderController, Actor);

public:
    ShaderController(const ActorBuildInfo* buildInfo);
    virtual ~ShaderController() { }

    u32 onExecute() override;

    f32 time;
};

REGISTER_PROFILE(ShaderController, ProfileID::ShaderController);

ShaderController::ShaderController(const ActorBuildInfo* buildInfo)
    : Actor(buildInfo)
    , time(0.0f)
{ }

u32 ShaderController::onExecute() {
    time++;

    ModelWrapper* model = DistantViewMgr::instance()->model;
    for (u32 i = 0; i < model->model->getMaterialNum(); i++) {
        MaterialNW* mat = static_cast<MaterialNW*>(model->model->getMaterial(i));

        s32 paramIdx = mat->materialObj->res->GetShaderParamIndex("amb_color0");
        if (paramIdx >= 0) {
            s32 offs = mat->materialObj->GetResShaderParam(paramIdx)->GetOffset();
            if (offs >= 0) {
                sead::Color4f* col = mat->materialObj->EditShaderParam<sead::Color4f>(paramIdx);
                col->set(time, 0.0f, 0.0f, 0.0f);
            } else {
                PRINT("offs invalid");
            }
        } else {
            PRINT("paramidx invalid");
        }
    }

    return 1;
}
