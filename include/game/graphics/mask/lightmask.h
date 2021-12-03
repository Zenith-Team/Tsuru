#pragma once

#include <game/graphics/mask/mask.h>

class LightMask : public Mask { // Size: 0x28
    // This class allows an actor to display visibility around it in darkness areas
    // Typically used in conjunction with LightSource to create light emitting actors
public:
    LightMask();

    bool init(sead::Heap* heap, u32 type) override;
    bool update() override;
    bool draw() override;

    f32 radius;
    f32 _8;
    sead::Vec3f position;
    void* _18;
    u32 _1C;
    u32 type;
    u32 _24;
};

static_assert(sizeof(LightMask) == 0x28, "LightMask size mismatch");
