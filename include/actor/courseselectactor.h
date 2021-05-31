#include "actor/baseactor.h"

class CourseSelectActor : public BaseActor {
    SEAD_RTTI_OVERRIDE(CourseSelectActor, BaseActor)

public:
    CourseSelectActor(const ActorBuildInfo* buildInfo);
    virtual ~CourseSelectActor();

    u32 beforeExecute() override;
    u32 beforeDraw() override;

    Vec3 position;
    Vec3 position2;
    Vec3 _68;
    Vec3 _74;
    Vec3 scale;
    Vec3 _8C;
    Vec3 _98;
    Vec3 _A4;
    u32 _B0;
    u32 rotation;
    u32 _B8;
    u32 _BC;
    u32 rotation2;
    u32 _C4;
    f32 _C8;
    f32 _CC;
    f32 _D0;
    f32 _D4;
    bool _D8;
};