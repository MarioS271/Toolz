/**
 * @file clearMain.hpp
 * @authors MarioS271
 */

#pragma once

#include <windows.h>
#include "class/renderer.hpp"
#include "helper/anchors.hpp"

void clearMain(Renderer& r) {
    COORD size = {
        anchor::right(),
        static_cast<SHORT>(anchor::bottom() - 2),
    };
    r.clearArea(anchor::topLeftVA(), size);
}