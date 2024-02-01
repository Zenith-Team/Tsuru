#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

typedef float f32;
typedef unsigned int u32;
typedef f32 MTX[3][4];
typedef f32 MTX44[3][4];

void ASM_MTXConcat(MTX a, MTX b, MTX o);
void ASM_MTXCopy(MTX n, MTX o);
void ASM_MTXIdentity(MTX o);
u32  ASM_MTXInverse(MTX n, MTX o);
void ASM_MTXTrans(MTX o, f32 x, f32 y, f32 z);
void ASM_MTXTranspose(MTX n, MTX o);
void ASM_MTXScale(MTX o, f32 x, f32 y, f32 z);
void ASM_MTX44Concat(MTX44 a, MTX44 b, MTX44 o);
void ASM_MTX44Copy(MTX44 n, MTX44 o);
void ASM_MTX44Identity(MTX44 o);

typedef f32 Vec[3];

void ASM_VECAdd(const Vec* a, const Vec* b, Vec* o);
void ASM_VECCrossProduct(const Vec* a, const Vec* b, Vec* o);
f32  ASM_VECDotProduct(const Vec* a, const Vec* b);
f32  ASM_VECMag(const Vec* v);
f32  ASM_VECSquareMag(const Vec* v);
void ASM_VECScale(const Vec* v, Vec* o, f32 t);
void ASM_VECSubtract(const Vec* a, const Vec* b, Vec* o);
f32  ASM_VECDistance(const Vec* a, const Vec* b);
f32  ASM_VECSquareDistance(const Vec* a, const Vec* b);

void ASM_MTXMultVec(MTX a, const Vec* b, Vec* o);
void ASM_MTXMultVecSR(MTX a, const Vec* b, Vec* o);

#ifdef __cplusplus
}
#endif // __cplusplus
