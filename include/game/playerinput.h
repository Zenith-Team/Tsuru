#pragma once

#include <types.h>

// TODO: finish this

class PlayerInput {
public:
    bool isUpPressed() const;
    bool isDownPressed() const;

    bool isUpHeld() const;
    bool isDownHeld() const;
    bool isLeftHeld() const;
    bool isRightHeld() const;

    bool isOnlyUpHeld() const;
    bool isOnlyDownHeld() const;

    u8 _0[0x94];
};
