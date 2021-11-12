#pragma once

#include <sead.h>
#include <types.h>

namespace agl { namespace lyr {

struct RenderInfo;

class DrawMethod : public sead::IDisposer {
public:
    typedef void (sead::TaskBase::*PTMF)(const RenderInfo& renderInfo); //? This is a hack, how does AGL handle this PTMF officially?

public:
    sead::SafeString name;
    u32 _18;
    u32 _1C;
    u32 _20;
    sead::TaskBase* _24;    //? Is this official?
    PTMF method;
    u32 _30;
    u32 _34;
    u32 _38;
    u32 _3C;
};

} }

#define MAKE_DRAW_METHOD(MEMBER, NAME, METHOD, LAYERNUM)                            \
    this-> ## MEMBER ## .name = NAME ## ;                                           \
    this-> ## MEMBER ## ._18 = 1;                                                   \
    this-> ## MEMBER ## ._20 = 0x10177234; /* Stolen vtable from GameOverScene */   \
    this-> ## MEMBER ## ._24 = this;                                                \
    this-> ## MEMBER ## .method = static_cast<agl::lyr::DrawMethod::PTMF>(METHOD);  \
    {                                                                               \
        agl::lyr::Layer* layer = agl::lyr::Renderer::instance()->layers.buffer[0];  \
        if (LAYERNUM < agl::lyr::Renderer::instance()->layers.size)                 \
            layer = agl::lyr::Renderer::instance()->layers.buffer[LAYERNUM];        \
        layer->pushBackDrawMethod(0, &this-> ## MEMBER);                            \
    } (void)0
