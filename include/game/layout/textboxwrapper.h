#pragma once

#include "nw/lyt/textbox.h"
#include "prim/seadSafeString.h"

class TextBoxWrapper : public nw::lyt::TextBox {
public:
    void setTextFromMSBT(const sead::SafeString& msbtKey, u32 count = 0, ...);

    f32 _104;
    f32 _108;
    u8 _10C;
    u32 _110;
    u8 _114;
};

static_assert(sizeof(TextBoxWrapper) == 0x118, "TextBoxWrapper size mismatch");
