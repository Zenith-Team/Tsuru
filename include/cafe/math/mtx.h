#pragma once

typedef unsigned int u32;
typedef float f32;

typedef f32 VEC[3];
typedef f32 MTX[3][4];
typedef f32 MTX44[4][4];

#ifdef __cplusplus
extern "C" {
#endif

void ASM_MTXConcat(MTX a, MTX b, MTX o);
void ASM_MTXCopy(MTX n, MTX o);
void ASM_MTXIdentity(MTX o);
u32  ASM_MTXInverse(MTX n, MTX o);
void ASM_MTXTranspose(MTX n, MTX o);
void ASM_MTXScale(MTX o, f32 x, f32 y, f32 z);
void ASM_MTX44Concat(MTX44 a, MTX44 b, MTX44 o);
void ASM_MTX44Copy(MTX44 n, MTX44 o);
void ASM_MTX44Identity(MTX44 o);

#ifdef __cplusplus
}
#endif
