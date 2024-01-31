#pragma once

#include "layer/aglDrawMethod.h"
#include "game/layout/layouthandler.h"
#include "tsuru/minipointerlist.h"

class LayoutRenderer {
    SEAD_SINGLETON_DISPOSER(LayoutRenderer);

public:
    void addLayout(LayoutHandler& layout) {
        this->layouts.append(&layout);
    }

private:
    LayoutRenderer();

    void render(const agl::lyr::RenderInfo& renderInfo);

    agl::lyr::DrawMethod drawMethod;

    MiniPointerList<LayoutHandler*, 0xFF> layouts;
};
