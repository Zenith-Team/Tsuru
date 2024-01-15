#include "types.h"
#include "log.h"
#include "game/distantview/distantviewmgr.h"

ASM_BEGIN
.include "macros.S"

.global ShaderBG_ASM
ShaderBG_ASM:
    mr r29, r3
    SafeBranch ShaderBG_Execute
    blr

ASM_END

extern "C" void ShaderBG_Execute(DistantViewMgr* self) {
    static f32 time = 0.0f;
    time++;

    for (u32 i = 0; i < self->model->model->getMaterialNum(); i++) {
        MaterialNW* mat = static_cast<MaterialNW*>(self->model->model->getMaterial(i));

        s32 paramIdx = mat->materialObj->res->GetShaderParamIndex("amb_color0");
        if (paramIdx >= 0) {
            s32 offs = mat->materialObj->GetResShaderParam(paramIdx)->GetOffset();
            if (offs >= 0) {
                //PRINT("Setting custom uniforms");
                sead::Color4f* col = mat->materialObj->EditShaderParam<sead::Color4f>(paramIdx);
                col->set(time, 0.0f, 0.0f, 0.0f);
            } else {
                PRINT("offs invalid");
            }
        } else {
            PRINT("paramidx invalid");
        }
    }
}
