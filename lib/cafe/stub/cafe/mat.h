#pragma once

typedef float f32;

typedef struct {
    union {
        struct {
            f32 _00, _01, _02, _03;
            f32 _10, _11, _12, _13;
            f32 _20, _21, _22, _23;
            f32 _30, _31, _32, _33;
        };
        f32 m[4][4];
        f32 a[16];
    };
} Mat44;
