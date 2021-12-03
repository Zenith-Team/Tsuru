#pragma once

typedef unsigned int u32;
class Mtx34;
class Mtx44;
namespace sead { template <typename T> class Vector3; }
typedef sead::Vector3<float> Vec3f;

extern "C" {

// MTX34
void ASM_MTXConcat(Mtx34* a, Mtx34* b, Mtx34* out);
u32  ASM_MTXInverse(Mtx34* src, Mtx34* dst);
void ASM_MTXMultVec(Mtx34* mtx, Vec3f* vec, Vec3f* out);

// MTX44
void ASM_MTX44Copy(Mtx44* src, Mtx44* dst);
void ASM_MTX44Identity(Mtx44* mtx);
void ASM_MTX44Concat(Mtx44* a, Mtx44* b, Mtx44* out);
void ASM_MTX44Transpose(Mtx44* mtx, Mtx44* out);
void ASM_MTX44MultVec(Mtx44* mtx, Vec3f* vec, Vec3f* out);

}
