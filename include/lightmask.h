#pragma once

#include "sead.h"
#include "util/vec3.h"

class LightMaskBase {
public:
    virtual bool init(sead::Heap* heap, u32 type) = 0;
    virtual bool update() = 0;
    virtual bool draw() = 0;
};

class LightMask : public LightMaskBase {  //? Dunno if it has a base class but the vtable is at 0x0 somehow 
public:
    LightMask();

    bool init(sead::Heap* heap, u32 type) override;
    bool update() override;
    bool draw() override;

    f32 radius;                     // Inited to 0.0
    f32 _8;                         // Inited to 0.0    //? Some sort of max radius thing maybe
    Vec3 position;                  // Inited to 0.0
    void* _18;                      // Pointer to a class
    void* _1C;                      // Pointer to a class
    u32 type;
    u32 _24;
};
