#pragma once

#include "types.h"

class Mtx44 {
public:
    union {
        f32 rows[4][4];
        f32 cells[16];
    };
};
