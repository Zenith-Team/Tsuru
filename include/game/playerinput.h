#pragma once

#include <sead/bitflag.h>
#include <tsuru/utils.h>

class PlayerInput {
public:
    PlayerInput();

    inline bool getButtonRight() { return nthBitRight(this->buttons.bits, 8); }
    inline bool getButtonLeft() { return nthBitRight(this->buttons.bits, 7); }
    inline bool getButtonDown() { return nthBitRight(this->buttons.bits, 6); }
    inline bool getButtonUp() { return nthBitRight(this->buttons.bits, 5); }
    inline bool getButtonJump() { return (nthBitRight(this->buttons.bits, 1) && nthBitRight(this->buttons.bits, 12)); }
    inline bool getButtonDash() { return (nthBitRight(this->buttons.bits, 3) && nthBitRight(this->buttons.bits, 2)); }

    u32 _0;
    u32 _4; // Shake?
    sead::BitFlag32 buttons;
    sead::BitFlag32 _C;
    u8 _10[0x38]; // Inlined struct
    u8 _48[0x38]; // Inlined struct
    sead::BitFlag32 _80;
    sead::BitFlag32 _84;
    u8 _88;
    u8 _89;
    u32 _8C;
    u32 _90;
};
