#pragma once

#include "types.h"
#include "game/states.h"

class MovementHandler {
public:
    ENUM_CLASS(MovementType,
        None,
        Rotation,
        Bolt,
        Path,
        BackForth
    );

public:
    MovementHandler();

    void link(const sead::Vector3f& position, u32 typeMask, u8 movementID);
    void execute();
    u32 getMaskForMovementType(u32 movementType);

    DECLARE_STATE(MovementHandler, FindController);
    DECLARE_STATE(MovementHandler, Linked);

    sead::Vector3f position;              // 0
    sead::Vector3f _C;                    // C
    sead::Vector3f _18;                   // 18
    sead::Vector3f _24;                   // 24
    u32 _30;                              // 30
    u32 _34;                              // 34
    u32 _38;                              // 38
    u32 _3C;                              // 3C
    u32 _40;                              // 40
    u32 _44;                              // 44
    u32 typeMask;                         // 48
    u8 movementID;                        // 4C
    u32 rotation;                         // 50
    u8 _54;                               // 54
    f32 _58;                              // 58
    u8 _5C[0x74 - 0x5C];                  // 5C
    u32 _74;                              // 74
    u32 _78;                              // 78
    u32 _7C;                              // 7C
    u32 _80;                              // 80
    u8 _84;                               // 84
    u8 _85;                               // 85
    u8 _86;                               // 86
    u8 _87;                               // 87
    u8 _88;                               // 88
    u8 _89;                               // 89
    u32 _8C;                              // 8C
    f32 _90;                              // 90
    u32 _94;                              // 94
    u8 _98[0xA0 - 0x98];                  // 98
    u32 _A0;                              // A0
    u32 _A4;                              // A4
    u32 _A8;                              // A8
    u32 _AC;                              // AC
    u32 _B0;                              // B0
    u32 _B4;                              // B4
    u32 _B8;                              // B8
    u32 _BC;                              // BC
    u8 _C0[0xD4 - 0xC0];                  // C0
    StateWrapper<MovementHandler> states; // D4
};
