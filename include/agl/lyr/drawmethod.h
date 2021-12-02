#pragma once

#include "sead/prim/seadNamable.h"
#include "sead/heap/seadDisposer.h"

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
    u32 _1C;
    u32 _20;
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

#define BIND_DRAW_METHOD(MEMBER, NAME, METHOD, LAYERNUM)                            \
    this-> ## MEMBER ## .INamableName = NAME ## ;                                   \
    this-> ## MEMBER ## ._18 = 1;                                                   \
    this-> ## MEMBER ## ._20 = 0x10177234; /* Stolen vtable from GameOverScene */   \
    this-> ## MEMBER ## ._24 = this;                                                \
    this-> ## MEMBER ## .method = METHOD;                                           \
    {   agl::lyr::Layer* layer = agl::lyr::Renderer::instance()->layers.buffer[0];  \
        if (LAYERNUM < agl::lyr::Renderer::instance()->layers.size)                 \
            layer = agl::lyr::Renderer::instance()->layers.buffer[LAYERNUM];        \
        layer->pushBackDrawMethod(0, &this-> ## MEMBER);                            \
    } (void)0
