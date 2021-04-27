#pragma once

#include "types.h"

namespace sead {

class Projection {
public:
    void* getDeviceProjectionMatrix();

    virtual bool checkDerivedRuntimeTypeInfo(void*);
    virtual void vf14() deleted;
    virtual ~Projection();
    //...

    u8 _0;
	u8 _1;
	u8 _2;
	u8 _3;
	u8 _4[64];
	u8 _44[64];
	u32 _84;
	f32 _88;
	f32 _8C;
};


}
