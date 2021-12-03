#pragma once

typedef float f32;
namespace sead { template <typename T> class Vector3; }
typedef sead::Vector3<f32> Vec3f;

void ASM_VECCrossProduct(Vec3f* a, Vec3f* b, Vec3f* out);
f32  ASM_VECDistance(Vec3f* a, Vec3f* b);
f32  ASM_VECMag(Vec3f* vec);
f32  ASM_VECSquareDistance(Vec3f* a, Vec3f* b);
