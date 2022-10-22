#pragma once

#include "types.h"
#include "sead/idisposer.h"
#include "sead/inamable.h"
#include "sead/task.h"

//! -----------------------------------------------------
//! THIS IS NOT AN OFFICIAL IMPLEMENTATION OF DRAWMETHOD.
//! JUST TEMPORARILY HERE UNTIL WE GET DELEGATE HEADERS.
//! -----------------------------------------------------

namespace agl { namespace lyr {

struct RenderInfo;

class DrawMethodImplBase : public sead::IDisposer, public sead::INamable { };

template <class TOwner>
class DrawMethodImpl : public DrawMethodImplBase {
public:
    typedef void (TOwner::*PTMF)(const RenderInfo& renderInfo);

public:
    u32 _18;
    u32 priority;
    void* _20;
    TOwner* _24;
    PTMF method;
    u32 _30;
    u32 _34;
    u32 _38;
    u32 _3C;
};

typedef DrawMethodImpl<sead::TaskBase> DrawMethod;

static_assert(sizeof(DrawMethod) == 0x40, "agl::lyr::DrawMethod size mismatch");

} }

extern int SafeStringVtable;

#define BIND_DRAW_METHOD(OBJECT, NAME, METHOD, LAYERNUM, OWNERPTR)                  \
    OBJECT ## .INamableName = NAME ## ;                                             \
    OBJECT ## ._18 = 1;                                                             \
    OBJECT ## ._20 = &SafeStringVtable;                                             \
    OBJECT ## ._24 = OWNERPTR;                                                      \
    OBJECT ## .method = METHOD;                                                     \
    {   agl::lyr::Layer* layer = agl::lyr::Renderer::instance()->layers.buffer[0];  \
        if (LAYERNUM < agl::lyr::Renderer::instance()->layers.size)                 \
            layer = agl::lyr::Renderer::instance()->layers.buffer[LAYERNUM];        \
        layer->pushBackDrawMethod(0, & ## OBJECT);                                  \
    } (void)0

#define BIND_DRAW_METHOD_TO_RENDERSTEP(OBJECT, NAME, METHOD, LAYERNUM, OWNERPTR, RS) \
    OBJECT ## .INamableName = NAME ## ;                                              \
    OBJECT ## ._18 = 1;                                                              \
    OBJECT ## ._20 = &SafeStringVtable;                                              \
    OBJECT ## ._24 = OWNERPTR;                                                       \
    OBJECT ## .method = METHOD;                                                      \
    {   agl::lyr::Layer* layer = agl::lyr::Renderer::instance()->layers.buffer[0];   \
        if (LAYERNUM < agl::lyr::Renderer::instance()->layers.size)                  \
            layer = agl::lyr::Renderer::instance()->layers.buffer[LAYERNUM];         \
        layer->pushBackDrawMethod(RS, & ## OBJECT);                                  \
    } (void)0