#pragma once

#include <types.h>

// TODO: finish this

class PlayerInput {
public:
    // @return Whether or not the owner player is currently pressing the Up button
    bool isUpPressed() const;
    // @return Whether or not the owner player is currently pressing the Down button
    bool isDownPressed() const;

    // @return Whether or not the owner player is currently holding the Up button
    bool isUpHeld() const;
    // @return Whether or not the owner player is currently holding the Down button
    bool isDownHeld() const;
    // @return Whether or not the owner player is currently holding the Left button
    bool isLeftHeld() const;
    // @return Whether or not the owner player is currently holding the Right button
    bool isRightHeld() const;

    // @return Whether or not the owner player is currently holding only the Up button
    bool isOnlyUpHeld() const;
    // @return Whether or not the owner player is currently holding only the Down button
    bool isOnlyDownHeld() const;

    u8 _0[0x94];
};
