#pragma once

#include "prim/seadBitFlag.h"
#include "tsuru/utils.h"

class PlayerInput {
public:
    PlayerInput();

    inline bool getButtonRight() { return this->buttons.isOnBit(7); }
    inline bool getButtonLeft() { return this->buttons.isOnBit(6); }
    inline bool getButtonDown() { return this->buttons.isOnBit(5); }
    inline bool getButtonUp() { return this->buttons.isOnBit(4); }
    inline bool getButtonJump() { return (this->buttons.isOnBit(0) && this->buttons.isOnBit(11)); }
    inline bool getButtonDash() { return (this->buttons.isOnBit(2) && this->buttons.isOnBit(1)); }

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
