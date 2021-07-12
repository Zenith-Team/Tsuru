#ifndef EFT_ANIMATION_H_
#define EFT_ANIMATION_H_

#include "types.h"

namespace nw { namespace eft {

struct KeyFrameAnim;

f32 CalcAnimKeyFrame(KeyFrameAnim* anim, f32 frame);

} } // namespace nw::eft

#endif // EFT_ANIMATION_H_
