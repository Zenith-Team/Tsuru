#pragma once

#include "sead/bitflag.h"
#include "sead/boundbox.h"
#include "sead/sphere.h"

namespace agl { namespace sdw {

class DepthShadow {
private:
    typedef sead::BitFlag32 (DepthShadow::*CheckAndUpdateBoundBoxFunc)(const sead::BoundBox3f&);
    typedef sead::BitFlag32 (DepthShadow::*CheckAndUpdateSphereFunc)(const sead::Sphere3f&);

public:
    DepthShadow();
    virtual ~DepthShadow();

    sead::BitFlag32 checkAndUpdate(const sead::BoundBox3f& box) {
        return (this->*checkAndUpdateBoundBox)(box);
    }

    sead::BitFlag32 checkAndUpdate(const sead::Sphere3f& sphere) {
        return (this->*checkAndUpdateSphere)(sphere);
    }

private:
    CheckAndUpdateBoundBoxFunc checkAndUpdateBoundBox;
    CheckAndUpdateSphereFunc checkAndUpdateSphere;
    u8 _10[0xC04 - 0x10];
};

static_assert(sizeof(DepthShadow) == 0xC08, "agl::sdw::DepthShadow size mismatch");

} }
