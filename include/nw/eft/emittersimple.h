#ifndef EFT_EMITTER_SIMPLE_H_
#define EFT_EMITTER_SIMPLE_H_

#include "nw/eft/emitter.h"

namespace nw { namespace eft {

class EmitterSimpleCalc : public EmitterCalc {
public:
    EmitterSimpleCalc(System* system)
        : EmitterCalc(system)
    { }

    virtual void CalcEmitter(EmitterInstance* emitter);
    virtual PtclType GetPtclType() const { return PtclType_Simple; }
    virtual u32 CalcParticle(EmitterInstance* emitter, CpuCore core, bool noCalcBehavior, bool noMakePtclAttributeBuffer);
    virtual u32 CalcChildParticle(EmitterInstance* emitter, CpuCore core, bool noCalcBehavior, bool noMakePtclAttributeBuffer) { return 0; }

    void EmitSameDistance(const SimpleEmitterData* data, EmitterInstance* emitter);
};
static_assert(sizeof(EmitterSimpleCalc) == 4, "EmitterSimpleCalc size mismatch");

} } // namespace nw::eft

#endif // EFT_EMITTER_SIMPLE_H_
