#pragma once

#include "sead.h"
#include "agl/lyr/debuginfo.h"

namespace agl { namespace lyr { class Layer : public sead::IDisposer {
public:
    u32 _10;
	sead::Viewport viewPort1;
	sead::Viewport viewPort2;
	u32 _44;
	u32 _48;
	u32 _4C;
	u32 _50;
	u32 _54;
	u32 _58;
	u32 _5C;
	u32 _60;
	u32 _64;
	u32 _68;
	f32 _6C;
	f32 _70;
	f32 _74;
	f32 _78;
	f32 _7C;
	sead::ListNode node;
	u32 _88;
	DebugInfo debugInfo;
};

}}
