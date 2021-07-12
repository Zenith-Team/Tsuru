#ifndef EFT_EMITTER_COMPLEX_H_
#define EFT_EMITTER_COMPLEX_H_

#include "nw/eft/emittersimple.h"

namespace nw { namespace eft {

class EmitterComplexCalc : public EmitterSimpleCalc {
public:
    EmitterComplexCalc(System* system)
        : EmitterSimpleCalc(system)
    { }

    virtual void CalcEmitter(EmitterInstance* emitter) { EmitterSimpleCalc::CalcEmitter(emitter); }
    virtual PtclType GetPtclType() const { return PtclType_Complex; }
    virtual u32 CalcParticle(EmitterInstance* emitter, CpuCore core, bool noCalcBehavior, bool noMakePtclAttributeBuffer);
    virtual u32 CalcChildParticle(EmitterInstance* emitter, CpuCore core, bool noCalcBehavior, bool noMakePtclAttributeBuffer);

    static void EmitChildParticle(EmitterInstance* emitter, PtclInstance* ptcl);

    static inline void CalcStripe(EmitterInstance* emitter, PtclInstance* ptcl, const StripeData* stripeData, const ComplexEmitterData* data, CpuCore core);
    static inline void EmitChildParticle(EmitterInstance* emitter, PtclInstance* ptcl, CpuCore core, const ChildData* childData);
    static void CalcComplex(EmitterInstance* emitter, PtclInstance* ptcl, CpuCore core);
};
static_assert(sizeof(EmitterComplexCalc) == 4, "EmitterComplexCalc size mismatch");

} } // namespace nw::eft

#endif // EFT_EMITTER_COMPLEX_H_
