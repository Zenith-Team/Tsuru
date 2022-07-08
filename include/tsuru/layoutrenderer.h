#pragma once

#include "game/layout/layouthandler.h"
#include "sead/list.h"

class LayoutRenderer {
public:
    static sead::TList<LayoutHandler*> layouts;

    static void render();
    static void addLayout(LayoutHandler* layout);
};
