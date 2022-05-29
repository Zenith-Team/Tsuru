#pragma once

#include "nw/lyt/layout.h"

class GameLayout : public nw::lyt::Layout {
    NW_RTTI_OVERRIDE(GameLayout, nw::lyt::Layout);

public:
    GameLayout();
    virtual ~GameLayout();

    nw::lyt::Pane* BuildPaneObj(u32, const void*, const void*, const void*) override;
    nw::lyt::Layout* BuildPartsLayout(const void*, const void*, const void*) override;
};
